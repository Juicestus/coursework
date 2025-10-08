       IDENTIFICATION DIVISION.
       PROGRAM-ID. MOB.
       DATA DIVISION.
       WORKING-STORAGE SECTION.
           01 i PIC 9 VALUE 0.
           01 j PIC 9 VALUE 0.
       PROCEDURE DIVISION.
       MAIN-PROC.
           PERFORM PRINT-LINE UNTIL i > 20.
           STOP RUN.
       PRINT-LINE.
           MOVE 0 TO j.
            PERFORM PRINT-HASH UNTIL j > i.
            PERFORM PRINT-ZERO UNTIL j > 20.
            DISPLAY '\n' WITH NO ADVANCING.
      //SET i UP BY 1.
            COMPUTE i = i + 1.
       PRINT-HASH.
            DISPLAY '#' WITH NO ADVANCING.
      //SET j UP BY 1.
            COMPUTE j = j + 1.
       PRINT-ZERO.
            DISPLAY '0' WITH NO ADVANCING.
      //SET j UP BY 1.
           COMPUTE j = j + 1.

        END PROGRAM MOB.

