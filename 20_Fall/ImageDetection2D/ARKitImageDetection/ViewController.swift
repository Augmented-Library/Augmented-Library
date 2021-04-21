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

        
        //reset AR elements
        self.sceneView.scene.rootNode.enumerateChildNodes { (node, stop) in
            node.removeFromParentNode()
        }
        
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
            
            
            
            switch detectedImageName{
                case "dataMangaement":
                    self.loadURL(imageName: detectedImageName)
                case "firebaseLogo",
                     "slackLogo":
                    //self.createAnAlert(imageName: detectedImageName)
                    self.createFlyer(imageName: detectedImageName)
                    print("DONE")
                default:
                    print("???")
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
        let db = Firestore.firestore()
        let flyersRef = db.collection("flyers")
        let flyerQuery = flyersRef.whereField("title", isEqualTo: imageName)
        // should just this TBH: 
        // db.collection("flyers").whereField("title", isEqualTo: imageName)
        flyerQuery.getDocuments() { (querySnapshot, err) in
            if let err = err {
                print("Error getting documents: \(err)")
            }
            else {
                print("IN THE ELSE PORTION")
                for document in querySnapshot!.documents {
                    let flyerTitle = document.get("title") as! String
                    let flyerDes = document.get("description") as! String
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
                }
            }
        }
    }
    
    func createFlyer(imageName: String){
        let db = Firestore.firestore()
        let flyersRef = db.collection("flyers")
        let flyerQuery = flyersRef.whereField("title", isEqualTo: imageName)
        // should just this TBH:
        // db.collection("flyers").whereField("title", isEqualTo: imageName)
        flyerQuery.getDocuments() { (querySnapshot, err) in
            if let err = err {
                print("Error getting documents: \(err)")
            }
            else {
                print("IN THE ELSE PORTION")
                for document in querySnapshot!.documents {
                    let flyerTitle = document.get("title") as! String
                    let flyerDes = document.get("description") as! String
                    
                    //creat a Text Geometry that has depth and a text
                    let text = SCNText(string: flyerTitle + "\n" + flyerDes, extrusionDepth: 1)
                    //create material object that sets material to green and the text has the material
                    let material = SCNMaterial()
                    text.materials = [material]
                    //create a node object with speficifed position and size
                    //set the text geometry to the node
                    let node = SCNNode()
                    //node.position = SCNVector3(x:0, y:0.2, z:-0.1)
                    node.scale = SCNVector3(x:0.005, y:0.005, z:0.005)
                    node.geometry = text
                    
                    
                    
                    //add the node to the sceneView
                    self.sceneView.scene.rootNode.addChildNode(node)
                    
                    //this should make the text always face the camera
                    
                    //EulerAngles doesn't work; it's titled around 45 degrees
                    //let eulerAngles = self.sceneView.session.currentFrame?.camera.eulerAngles
                    //node.eulerAngles = SCNVector3(eulerAngles?.x ?? 0, eulerAngles?.y ?? 0, eulerAngles?.z ?? 0 + .pi/2)
                    
                    //text doesn't appear
                    //node.constraints=[SCNBillboardConstraint()]
                    
                    //text doesn't appear with this method too
                    //let billboardConstraint = SCNBillboardConstraint()
                    //billboardConstraint.freeAxes = SCNBillboardAxis.Y
                    //node.constraints=[billboardConstraint]
                    
                    //enable lighting to display shadows
                    self.sceneView.autoenablesDefaultLighting = true
                    
                    print("CREATED")
                }
            }
        }
    }
    
}
