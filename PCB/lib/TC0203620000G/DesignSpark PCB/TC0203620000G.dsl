SamacSys ECAD Model
1579225/279119/2.50/2/4/Connector

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "c195_h130"
		(holeDiam 1.3)
		(padShape (layerNumRef 1) (padShapeType Ellipse)  (shapeWidth 1.950) (shapeHeight 1.950))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 1.950) (shapeHeight 1.950))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "TC0203620000G" (originalName "TC0203620000G")
		(multiLayer
			(pad (padNum 1) (padStyleRef c195_h130) (pt 0.000, 0.000) (rotation 90))
			(pad (padNum 2) (padStyleRef c195_h130) (pt 5.000, 0.000) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 2.500, 0.450) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.1 4.2) (pt 8.1 4.2) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt 8.1 4.2) (pt 8.1 -3.3) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt 8.1 -3.3) (pt -3.1 -3.3) (width 0.2))
		)
		(layerContents (layerNumRef 28)
			(line (pt -3.1 -3.3) (pt -3.1 4.2) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.1 4.2) (pt 8.1 4.2) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 8.1 4.2) (pt 8.1 -3.3) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 8.1 -3.3) (pt -3.1 -3.3) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -3.1 -3.3) (pt -3.1 4.2) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt -4.1 5.2) (pt 9.1 5.2) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 9.1 5.2) (pt 9.1 -4.3) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt 9.1 -4.3) (pt -4.1 -4.3) (width 0.1))
		)
		(layerContents (layerNumRef 30)
			(line (pt -4.1 -4.3) (pt -4.1 5.2) (width 0.1))
		)
	)
	(symbolDef "TC0203620000G" (originalName "TC0203620000G")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "TC0203620000G" (originalName "TC0203620000G") (compHeader (numPins 2) (numParts 1) (refDesPrefix J)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "TC0203620000G"))
		(attachedPattern (patternNum 1) (patternName "TC0203620000G")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Mouser Part Number" "649-TC02036200J0G")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Amphenol-Anytek/TC0203620000G?qs=Mv7BduZupUiHURQaUHJ1XQ%3D%3D")
		(attr "Manufacturer_Name" "Amphenol")
		(attr "Manufacturer_Part_Number" "TC0203620000G")
		(attr "Description" "Fixed Terminal Blocks 500 TB WIR PRO 180D")
		(attr "Datasheet Link" "https://componentsearchengine.com/Datasheets/1/TC0203620000G.pdf")
		(attr "Height" "10.5 mm")
	)

)
