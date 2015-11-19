
Nephelium Inc. (R)
All Rights Reserved (C)

Authors	:Nirojan Selwanathan
		 K D Kasun Madusanka
		 Dehan De Croos
		 Prasanna Shanmugaraja


------------------------------------------------------------------
					main program structure
------------------------------------------------------------------

	IF NOT SYSTEM CONFIGURED THEN
		INIT CONFIGURATION 
		{
			CONFIG GENERAL SYSTEM SETTINGS
			CONFIG CAMERA NETWORK GRAPH
		}
	ENDIF
	
	INIT SYSTEM    // know  how many cameras(from graph),  

	INIT MULTIPROCESSING ACCORDING TO NUMBER OF CAMERAS IN NETWORK GRAPH

[START MULTI PROCESS SEGMENT] -------------------------
	
	// LOCAL VARIABLES FOR ONE CAMERA
	COLLECTION OF BLOBS --> B									--> blobs
	COLLECTION OF HUMAN BLOBS TRACK IN THIS CAMERA --> H		--> human_blobs
	COLLECTION OF MISSING HUMAN BLOBS --> M						--> missed_human_blobs
	COLLECTION OF UNIDENTIFIED BLOBS --> U						--> unindentified_blobs
	COLLECTION OF POSSIBLE PROFILES --> P						--> possible_profiles

	// PROCESS
	FOR EACH FRAME  IN VIDEO
	{
		B = BLOB DETECTION IN THE FRAME (FRAME)
		
		IF "H" IS EMPTY THEN
			U = B
		ELSE
			{U, H-updated, M} = MAP PREDICTED WITH CURRENT POINTS (H, B)
			KALMAN UPDATE OF ALL H // PREDICT NEXT SET OF POINTS
		ENDIF
		
		FOR EACH i IN U
		{
			IF "SEARCH IN CENTRAL DB (i)" THEN
				ADD i TO H
				REMOVE i FROM U
		}

		NEW_H = HUMAN DETECTION AND FEATURE EXTRACTION (U, P, FRAME)
		INIT KALMAN FOR NEW_H
		H += NEW_H
		UPDATE HUMAN PROFILES IN CETRAL DB (H)

		[NEW THREAD]
			VALIDATE MISSING HUMAN BLOBS - M // identify whether exit or vanished
			IF ANY M VANISHED THEN
				WARNING
			ELSE WHEN EXIT
				GET POSSIBLE NEXT CAMERAS IN NETWORK GRAPH FOR ALL M-exited
				SEND PROFILES TO RELEVENT CAMERA
		[END OF NEW THREAD]

		// REFRESH LOCAL VARIABLES
		CLEAR B, M, U
	}
[END OF MULTI PROCESS SEGMENT] ------------------------
