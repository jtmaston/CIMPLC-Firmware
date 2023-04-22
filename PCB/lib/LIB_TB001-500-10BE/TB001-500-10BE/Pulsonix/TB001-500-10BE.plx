PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//5147598/279119/2.50/10/4/Connector

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c180_h120"
		(holeDiam 1.2)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.8) (shapeHeight 1.8))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.8) (shapeHeight 1.8))
	)
	(padStyleDef "s180_h120"
		(holeDiam 1.2)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 1.8) (shapeHeight 1.8))
		(padShape (layerNumRef 16) (padShapeType Rect)  (shapeWidth 1.8) (shapeHeight 1.8))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "SHDR10W100P0X500_1X10_5000X900" (originalName "SHDR10W100P0X500_1X10_5000X900")
		(multiLayer
			(pad (padNum 1) (padStyleRef s180_h120) (pt 0, 0) (rotation 90))
			(pad (padNum 2) (padStyleRef c180_h120) (pt 5, 0) (rotation 90))
			(pad (padNum 3) (padStyleRef c180_h120) (pt 10, 0) (rotation 90))
			(pad (padNum 4) (padStyleRef c180_h120) (pt 15, 0) (rotation 90))
			(pad (padNum 5) (padStyleRef c180_h120) (pt 20, 0) (rotation 90))
			(pad (padNum 6) (padStyleRef c180_h120) (pt 25, 0) (rotation 90))
			(pad (padNum 7) (padStyleRef c180_h120) (pt 30, 0) (rotation 90))
			(pad (padNum 8) (padStyleRef c180_h120) (pt 35, 0) (rotation 90))
			(pad (padNum 9) (padStyleRef c180_h120) (pt 40, 0) (rotation 90))
			(pad (padNum 10) (padStyleRef c180_h120) (pt 45, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -2.75 -4.25) (pt -2.75 5.25) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -2.75 5.25) (pt 47.75 5.25) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 47.75 5.25) (pt 47.75 -4.25) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 47.75 -4.25) (pt -2.75 -4.25) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.5 -4) (pt -2.5 5) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -2.5 5) (pt 47.5 5) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 47.5 5) (pt 47.5 -4) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 47.5 -4) (pt -2.5 -4) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 -4) (pt 47.5 -4) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 47.5 -4) (pt 47.5 5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 47.5 5) (pt -2.5 5) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -2.5 5) (pt -2.5 0) (width 0.2))
		)
	)
	(symbolDef "TB001-500-10BE" (originalName "TB001-500-10BE")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 4) (pt 0 mils -300 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -325 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 5) (pt 0 mils -400 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -425 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 6) (pt 0 mils -500 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -525 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 7) (pt 0 mils -600 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -625 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 8) (pt 0 mils -700 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -725 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 9) (pt 0 mils -800 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -825 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 10) (pt 0 mils -900 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -925 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -1000 mils) (width 6 mils))
		(line (pt 600 mils -1000 mils) (pt 200 mils -1000 mils) (width 6 mils))
		(line (pt 200 mils -1000 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 650 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "TB001-500-10BE" (originalName "TB001-500-10BE") (compHeader (numPins 10) (numParts 1) (refDesPrefix J)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "3") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "4" (pinName "4") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "5" (pinName "5") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "6" (pinName "6") (partNum 1) (symPinNum 6) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "7" (pinName "7") (partNum 1) (symPinNum 7) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "8" (pinName "8") (partNum 1) (symPinNum 8) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "9" (pinName "9") (partNum 1) (symPinNum 9) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "10" (pinName "10") (partNum 1) (symPinNum 10) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "TB001-500-10BE"))
		(attachedPattern (patternNum 1) (patternName "SHDR10W100P0X500_1X10_5000X900")
			(numPads 10)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "5")
				(padNum 6) (compPinRef "6")
				(padNum 7) (compPinRef "7")
				(padNum 8) (compPinRef "8")
				(padNum 9) (compPinRef "9")
				(padNum 10) (compPinRef "10")
			)
		)
		(attr "Mouser Part Number" "490-TB001-500-10BE")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/CUI-Devices/TB001-500-10BE?qs=vLWxofP3U2zH1ZAwWBP5mg%3D%3D")
		(attr "Manufacturer_Name" "CUI Devices")
		(attr "Manufacturer_Part_Number" "TB001-500-10BE")
		(attr "Description" "Fixed Terminal Blocks")
		(attr "<Hyperlink>" "https://componentsearchengine.com/Datasheets/1/TB001-500-10BE.pdf")
		(attr "<Component Height>" "12.5")
		(attr "<STEP Filename>" "TB001-500-10BE.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)
