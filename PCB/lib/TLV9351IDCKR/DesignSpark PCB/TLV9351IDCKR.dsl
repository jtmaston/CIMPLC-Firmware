SamacSys ECAD Model
14978695/279119/2.50/5/3/Integrated Circuit

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r120_40"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.4) (shapeHeight 1.2))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "SOT65P210X110-5N" (originalName "SOT65P210X110-5N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r120_40) (pt -0.95, 0.65) (rotation 90))
			(pad (padNum 2) (padStyleRef r120_40) (pt -0.95, 0) (rotation 90))
			(pad (padNum 3) (padStyleRef r120_40) (pt -0.95, -0.65) (rotation 90))
			(pad (padNum 4) (padStyleRef r120_40) (pt 0.95, -0.65) (rotation 90))
			(pad (padNum 5) (padStyleRef r120_40) (pt 0.95, 0.65) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.8 1.325) (pt 1.8 1.325) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.8 1.325) (pt 1.8 -1.325) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.8 -1.325) (pt -1.8 -1.325) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.8 -1.325) (pt -1.8 1.325) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.625 1) (pt 0.625 1) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.625 1) (pt 0.625 -1) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.625 -1) (pt -0.625 -1) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.625 -1) (pt -0.625 1) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.625 0.35) (pt 0.025 1) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.55 1.1) (pt -0.35 1.1) (width 0.2))
		)
	)
	(symbolDef "TLV9351IDCKR" (originalName "TLV9351IDCKR")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 3) (pt 0 mils -200 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -225 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 4) (pt 1000 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(pin (pinNum 5) (pt 1000 mils -100 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 770 mils -125 mils) (rotation 0]) (justify "Right") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 800 mils 100 mils) (width 6 mils))
		(line (pt 800 mils 100 mils) (pt 800 mils -300 mils) (width 6 mils))
		(line (pt 800 mils -300 mils) (pt 200 mils -300 mils) (width 6 mils))
		(line (pt 200 mils -300 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 850 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "TLV9351IDCKR" (originalName "TLV9351IDCKR") (compHeader (numPins 5) (numParts 1) (refDesPrefix IC)
		)
		(compPin "1" (pinName "IN+") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "V-") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "3" (pinName "IN-") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "4" (pinName "OUT") (partNum 1) (symPinNum 4) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "5" (pinName "V+") (partNum 1) (symPinNum 5) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "TLV9351IDCKR"))
		(attachedPattern (patternNum 1) (patternName "SOT65P210X110-5N")
			(numPads 5)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
				(padNum 4) (compPinRef "4")
				(padNum 5) (compPinRef "5")
			)
		)
		(attr "Mouser Part Number" "595-TLV9351IDCKR")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/TLV9351IDCKR?qs=DRkmTr78QAQETvxeOeABCA%3D%3D")
		(attr "Manufacturer_Name" "Texas Instruments")
		(attr "Manufacturer_Part_Number" "TLV9351IDCKR")
		(attr "Description" "Operational Amplifiers - Op Amps 40-V, single 3.5-MHz, RRO, MUX-friendly operational amplifier for cost-sensitive systems 5-SC70 -40 to 125")
		(attr "Datasheet Link" "https://www.ti.com/lit/gpn/TLV9351")
		(attr "Height" "1.1 mm")
	)

)