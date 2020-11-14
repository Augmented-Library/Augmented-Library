/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Main view controller for the AR experience.
*/

import ARKit
import SceneKit
import UIKit
import Firebase

class ViewController: UIViewController, ARSCNViewDelegate {
    
    @IBOutlet var sceneView: ARSCNView!
    
    @IBOutlet weak var blurView: UIVisualEffectView!
    
    var docRef : DocumentReference!
    
    /// The view controller that displays the status and "restart experience" UI.
    lazy var statusViewController: StatusViewController = {
        return children.lazy.compactMap({ $0 as? StatusViewController }).first!
    }()
    
    /// A serial queue for thread safety when modifying the SceneKit node graph.
    let updateQueue = DispatchQueue(label: Bundle.main.bundleIdentifier! +
        ".serialSceneKitQueue")
    
    /// Convenience accessor for the session owned by ARSCNView.
    var session: ARSession {
        return sceneView.session
    }
    
    // MARK: - View Controller Life Cycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        sceneView.delegate = self
        sceneView.session.delegate = self

        // Hook up status view controller callback(s).
        statusViewController.restartExperienceHandler = { [unowned self] in
            self.restartExperience()
        }
    }

	override func viewDidAppear(_ animated: Bool) {
		super.viewDidAppear(animated)
		
		// Prevent the screen from being dimmed to avoid interuppting the AR experience.
		UIApplication.shared.isIdleTimerDisabled = true

        // Start the AR experience
        resetTracking()
	}
	
	override func viewWillDisappear(_ animated: Bool) {
		super.viewWillDisappear(animated)

        session.pause()
	}

    // MARK: - Session management (Image detection setup)
    
    /// Prevents restarting the session while a restart is in progress.
    var isRestartAvailable = true

    /// Creates a new AR configuration to run on the `session`.
    /// - Tag: ARReferenceImage-Loading
	func resetTracking() {
        
        guard let referenceImages = ARReferenceImage.referenceImages(inGroupNamed: "AR Class Types", bundle: nil) else {
            fatalError("Missing expected asset catalog resources.")
        }
        
        let configuration = ARWorldTrackingConfiguration()
        configuration.detectionImages = referenceImages
        session.run(configuration, options: [.resetTracking, .removeExistingAnchors])

        statusViewController.scheduleMessage("Look around to detect images", inSeconds: 7.5, messageType: .contentPlacement)
	}

    // MARK: - ARSCNViewDelegate (Image detection results)
    /// - Tag: ARImageAnchor-Visualizing
    func renderer(_ renderer: SCNSceneRenderer, didAdd node: SCNNode, for anchor: ARAnchor) {
        guard let imageAnchor = anchor as? ARImageAnchor else { return }
        let referenceImage = imageAnchor.referenceImage
        updateQueue.async {
            
            // Create a plane to visualize the initial position of the detected image.
            let plane = SCNPlane(width: referenceImage.physicalSize.width,
                                 height: referenceImage.physicalSize.height)
            let planeNode = SCNNode(geometry: plane)
            planeNode.opacity = 0.25
            
            /*
             `SCNPlane` is vertically oriented in its local coordinate space, but
             `ARImageAnchor` assumes the image is horizontal in its local space, so
             rotate the plane to match.
             */
            planeNode.eulerAngles.x = -.pi / 2
            
            /*
             Image anchors are not tracked after initial detection, so create an
             animation that limits the duration for which the plane visualization appears.
             */
            planeNode.runAction(self.imageHighlightAction)
            
            // Add the plane visualization to the scene.
            node.addChildNode(planeNode)
            
            //Get URL based on name of detected image
            let detectedImageName = referenceImage.name ?? ""
            
            if(detectedImageName != "firebaseLogo"){
                self.loadURL(imageName: detectedImageName)
            }
            else{
                switch detectedImageName{
                    case "firebaseLogo":
                        self.createAnAlert(imageName: detectedImageName)
                        print("DONE")
                        
                    default:
                        print("???")
                }
            }
            
        }

        DispatchQueue.main.async {
            let imageName = referenceImage.name ?? ""
            self.statusViewController.cancelAllScheduledMessages()
            self.statusViewController.showMessage("Detected image “\(imageName)”")
        }
    }

    var imageHighlightAction: SCNAction {
        return .sequence([
            .wait(duration: 0.25),
            .fadeOpacity(to: 0.85, duration: 0.25),
            .fadeOpacity(to: 0.15, duration: 0.25),
            .fadeOpacity(to: 0.85, duration: 0.25),
            .fadeOut(duration: 0.5),
            .removeFromParentNode()
        ])
    }
    
    func loadURL(imageName: String){
        var libCalURL = ""
        switch imageName {
            case "dataManagement":
                libCalURL = "https://nyu.libcal.com/calendar?cid=1564&t=g&d=0000-00-00&cal=1564&ct=4295&inc=0"
            default:
                libCalURL = ""
            }
        if let url = URL(string: libCalURL) {
            DispatchQueue.main.async {
                UIApplication.shared.open(url)
            }
        }
    }
    
    func getTitle(imageName: String){
        
    }
    
    func createAnAlert(imageName: String){
        print("print")
        let db = Firestore.firestore()
        //self.ref = Database.database().reference().child("Posters").child(imageName);
        
        
        let flyersRef = db.collection("flyers")
        let flyerQuery = flyersRef.whereField("title", isEqualTo: imageName)
        print("BEGIN QUERY")
        flyerQuery.getDocuments() { (querySnapshot, err) in
            if let err = err {
                print("Error getting documents: \(err)")
            }
            else {
                for document in querySnapshot!.documents {
                    /*
                    let docId = document.documentID
                    let latMax = document.get("latMax") as! String
                    let latMin = document.get("latMin") as! String
                    let lonMax = document.get("lonMax") as! String
                    let lonMin = document.get("lonMin") as! String
                    print(docId, latMax, latMin, lonMax, lonMin)
                    */
                    let flyerTitle = document.get("title") as! String
                    let flyerDes = document.get("description") as! String
                    // let flyerLink = document.get("description") as! String
                    //self.statusViewController.showMessage("Detected image “\(fbDescription)”")
                    
                    
                    let alert = UIAlertController(
                        title: flyerTitle,
                        message: flyerDes,
                        preferredStyle: .alert
                    )
                    alert.addAction(UIAlertAction(
                        title: "YES", style: .default, handler: nil
                    ))
                    alert.addAction(UIAlertAction(
                        title: "NO", style: .cancel, handler: nil
                    ))
                    
                    self.present(alert, animated: true)
                    print("ALERT CREATED")
                }
                
            }
            
            
        }
        print("END QUERY")
        
        /*
        flyerQuery.getDocuments() { (querySnapshot, err) in
            if let err = err {
                print("Error getting documents: \(err)")
            } else {
                for document in querySnapshot!.documents {
                    print("\(document.documentID) => \(document.data())")
                }
            }
        }
        
        
        self.ref.observeSingleEvent(of: .value, with: {(snapshot) in
            if(!snapshot.exists()){
                return
            }
            let value = snapshot.value as? NSDictionary
            let fbTitle = value?["title"] as? String ?? ""
            let fbDescription = value?["description"] as? String ?? ""
            //self.statusViewController.showMessage("Detected image “\(fbDescription)”")
            let alert = UIAlertController(
                title: fbTitle,
                message: fbDescription,
                preferredStyle: .alert
            )
            alert.addAction(UIAlertAction(
                title: "YES", style: .default, handler: nil
            ))
            alert.addAction(UIAlertAction(
                title: "NO", style: .cancel, handler: nil
            ))
            
            self.present(alert, animated: true)
        })
        */
    }
    
}
