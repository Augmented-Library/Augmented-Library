//
//  ViewController.swift
//  DibnerTour
//
//  Created by Andrew Qu on 5/5/20.
//  Copyright © 2020 Andrew Qu. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet var myUIImageView: UIImageView!
    @IBOutlet var studyRoomButton: UIButton?
    @IBOutlet var stairButton: UIButton?
    @IBOutlet var shelvesButton: UIButton?
    @IBOutlet var studyRoomsInfo: UIView?
    @IBOutlet var printersInfo: UIView?
    @IBOutlet var frontDeskInfo: UIView?
    @IBOutlet var floorPlanView: UIView!
    @IBOutlet var libraryServicesView: UIView!
    @IBOutlet var thirdFloorServicesLabel: UILabel!
    @IBOutlet var fourthFloorServicesLabel: UILabel!
    @IBOutlet var ongoingEventsLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        studyRoomsInfo?.isHidden = true
        printersInfo?.isHidden = true
        frontDeskInfo?.isHidden = true
        floorPlanView.isHidden = true
        libraryServicesView.isHidden = true
        let thirdServicesString = ["Adaptive technology room",
                           "Bathrooms",
                           "Charging station",
                           "Computer lab",
                           "Course reserves",
                           "Equipment loans",
                           "Exhibits and events",
                           "Group study rooms",
                           "Poly archives",
                           "Printing",
                           "Reference consultations",
                           "Workshops"
        ]
        thirdFloorServicesLabel.attributedText = add(stringList: thirdServicesString, font:thirdFloorServicesLabel.font, bullet:"+")
        let fourthServicesString = ["Group study rooms",
                                    "Holocube room",
                                    "Individual study rooms",
                                    "Scanners",
                                    "Snack lounge"
        ]
        fourthFloorServicesLabel.attributedText = add(stringList: fourthServicesString, font:fourthFloorServicesLabel.font, bullet:"+")
    }
    
    func add(stringList: [String],
             font: UIFont,
             bullet: String = "\u{2022}",
             indentation: CGFloat = 20,
             lineSpacing: CGFloat = 1,
             paragraphSpacing: CGFloat = 1,
             textColor: UIColor = .white,
             bulletColor: UIColor = .purple) -> NSAttributedString {

        let textAttributes: [NSAttributedString.Key: Any] = [NSAttributedString.Key.font: font, NSAttributedString.Key.foregroundColor: textColor]
        let bulletAttributes: [NSAttributedString.Key: Any] = [NSAttributedString.Key.font: font, NSAttributedString.Key.foregroundColor: bulletColor]

        let paragraphStyle = NSMutableParagraphStyle()
        let nonOptions = [NSTextTab.OptionKey: Any]()
        paragraphStyle.tabStops = [
            NSTextTab(textAlignment: .left, location: indentation, options: nonOptions)]
        paragraphStyle.defaultTabInterval = indentation
        //paragraphStyle.firstLineHeadIndent = 0
        //paragraphStyle.headIndent = 20
        //paragraphStyle.tailIndent = 1
        paragraphStyle.lineSpacing = lineSpacing
        paragraphStyle.paragraphSpacing = paragraphSpacing
        paragraphStyle.headIndent = indentation

        let bulletList = NSMutableAttributedString()
        for string in stringList {
            let formattedString = "\(bullet)\t\(string)\n"
            let attributedString = NSMutableAttributedString(string: formattedString)

            attributedString.addAttributes(
                [NSAttributedString.Key.paragraphStyle : paragraphStyle],
                range: NSMakeRange(0, attributedString.length))

            attributedString.addAttributes(
                textAttributes,
                range: NSMakeRange(0, attributedString.length))

            let string:NSString = NSString(string: formattedString)
            let rangeForBullet:NSRange = string.range(of: bullet)
            attributedString.addAttributes(bulletAttributes, range: rangeForBullet)
            bulletList.append(attributedString)
        }

        return bulletList
    }
    
    @IBAction func studyRoomsButtonPressed(_ sender: UIButton) {
        studyRoomsInfo?.isHidden = !(studyRoomsInfo?.isHidden ?? false)
    }
    
    @IBAction func printersButtonPressed(_ sender: UIButton) {
        printersInfo?.isHidden = !(printersInfo?.isHidden ?? false)
    }
    
    @IBAction func frontDeskButtonPressed(_ sender: UIButton) {
        frontDeskInfo?.isHidden = !(frontDeskInfo?.isHidden ?? false)
    }
    
    @IBAction func floorPlanButtonPressed(_ sender: UIButton) {
        ongoingEventsLabel.isHidden = true
        floorPlanView.isHidden = false
    }
    
    @IBAction func floorPlanCloseButtonPressed(_ sender: UIButton) {
        floorPlanView.isHidden = true
        ongoingEventsLabel.isHidden = false
    }
    
    @IBAction func libraryServicesButtonPressed(_ sender: UIButton) {
        ongoingEventsLabel.isHidden = true
        libraryServicesView.isHidden = false
    }
    
    @IBAction func libraryServicesCloseButtonPressed(_ sender: UIButton) {
        libraryServicesView.isHidden = true
        ongoingEventsLabel.isHidden = false
    }
}

