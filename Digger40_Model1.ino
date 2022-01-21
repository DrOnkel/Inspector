

#include <Servo.h>
#define NUMBEROFSWINGSTODEFINE  8



#define NOFTUBEZ 8
#define NOFPOINTZ 16
#define NOFMODES 20

signed char Shift[8]={0,5,-5,0,-5,9,5,0};

byte Points [2] [NOFTUBEZ] [NOFPOINTZ] = {

  //обозначить где какие сервы , где какая труба !!!
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //First modul
  // THIS is for right wing of TE :
  // M0
  5, 14, 20, 25, 30, 34, 39, 42, 46, 50, 54, 57, 61, 111, 68, 61,
  15, 21, 26, 30, 34, 38, 42, 46, 50, 53, 57, 60, 64, 111, 68, 61,
  21, 25, 30, 34, 38, 42, 45, 49, 53, 56, 60, 63, 67, 111, 68, 61,
  24, 29, 33, 37, 40, 44, 48, 52, 55, 59, 62, 66, 69, 111, 68, 61,
  27, 31, 35, 39, 43, 47, 50, 54, 58, 61, 65, 68, 72, 111, 68, 61,
  30, 34, 38, 41, 45, 49, 52, 56, 60, 63, 67, 71, 74, 111, 68, 61,
  32, 36, 40, 43, 47, 50, 54, 58, 62, 65, 69, 73, 77, 111, 68, 61,
  34, 38, 41, 45, 49, 52, 56, 59, 63, 67, 71, 75, 79, 111, 68, 61,




  // M1
  130, 132, 134, 137, 140, 143, 146, 150, 153, 157, 162, 166, 171, 149, 80, 80, // !!! no less than 65
  123, 125, 127, 130, 133, 136, 140, 143, 147, 151, 156, 160, 165, 149, 80, 80,
  116, 118, 121, 124, 127, 130, 134, 137, 141, 145, 150, 154, 159, 149, 80, 80,
  109, 112, 114, 117, 120, 124, 128, 132, 136, 140, 144, 149, 154, 149, 80, 80,
  102, 105, 108, 111, 114, 118, 122, 126, 130, 135, 139, 144, 149, 149, 80, 80,
  95, 98, 101, 104, 108, 112, 116, 120, 125, 129, 134, 139, 144, 149, 80, 80,
  87, 90, 93, 97, 101, 105, 109, 114, 119, 124, 129, 134, 140, 149, 80, 80,
  79, 82, 86, 89, 94, 98, 103, 108, 113, 119, 124, 130, 135, 149, 80, 80


  // THIS is for left wing of TE

};
// 4 - is for servos , 8 - is for diametr if tube , 16 - is for steps. Seems like a  "X Y Z cube " where x - servos and hight , y - diametr of tube and wide , z - is for number of step and depth .
byte Mode0, OldMode0, CommandMode, OldCommandMode, Mode2, OldMode2, Mode1, OldMode1;
// unsigned long TimerInt;
unsigned int TimerT;
byte PrintOrNo = 1;

int PauseLoop = 100;

Servo servo1 ;
Servo servo0 ;
Servo servo2 ;
Servo servo3 ;

Servo servo4 ;
Servo servo5 ;
Servo servo6 ;
Servo servo7 ;




byte NofStep[2] = {0, 0} , NofDiam [2] = {7, 7} ; // Noofstep - just to inicialize , NoofDiam 2 is for 2 elements of all motion of model  .
//Recording at 07.08: this values in arrays - is for start
void setup() {

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("Digger v40 Model 2  date 20211109 "));
  pinMode (13 , OUTPUT);

  pinMode (2, INPUT_PULLUP); //sensor of diametr tube 0
  pinMode (3, INPUT_PULLUP); //sensor of diametr tube 1
  // pinMode (12, INPUT_PULLUP);


  servo0.attach (5);
  servo1.attach (6);
  servo2.attach (7);
  servo3.attach (8);
  servo4.attach (9);
  servo5.attach (10);
  servo6.attach (11);
  servo7.attach (12);
}

void loop() {


  switch (Mode0)
  {
    case 0:
      ;
      break;

    case 1: //tube select
      {
        if (OldMode0 != 1)
        {
          NofDiam[0] = 7;
          OldMode0 = 1;
          if (PrintOrNo)
            Serial.println(F("319"));
        }
        else
        {
          if (digitalRead(2) == LOW)
          {
            if (PrintOrNo)
            {
              Serial.print(F("Tube seclected = "));
              Serial.println(NofDiam[0]);
            }
            Mode0 = 15;
          }
          else
          {
            if (NofDiam[0] == 0)
            {
              Mode0 = 16;
              if (PrintOrNo)
              {
                Serial.print(F("Tube seclection failed "));
              }
            }
            else
            {
              NofDiam[0]--;
              if (PrintOrNo)
              {
                Serial.print(F("Tube seclection now DIAM = "));
                Serial.println(NofDiam[0]);
              }
            }


          }

        }
      }
      break;

    case 2: // Head Go Forward
      {
        if (NofStep[0] < 12)
        {
          NofStep[0]++;

        }
        else if (NofStep[0] > 12)
        {
          NofStep[0] = 0;

        }
        else
        {
          Mode0 = 5;


        }
      }  //END case 2
      break;

    case 3: // Return Step Forward
      {

        if (NofStep[0] < 13)
        {
          NofStep[0] = 13;

        }
        else if (NofStep[0] < 15)
        {
          NofStep[0]++;

        }
        else
        {
          Mode0 = 6;


        }
      }  //END case 3
      break;















    case 4: // Head Step Back
      {
        if (NofStep[0] > 12)
        {
          NofStep[0] = 12;

        }
        else if (NofStep[0] > 0)
        {
          NofStep[0]--;

        }
        else
        {
          Mode0 = 9;


        }
      }  //END case 4
      break;

    case 7: // Return Step Forward
      {

        if (NofStep[0] < 13)
        {
          NofStep[0] = 15;

        }
        else if (NofStep[0] > 13)
        {
          NofStep[0]--;

        }
        else
        {
          Mode0 = 8;


        }
      }  //END case 7
      break;

  }


  switch (Mode1)
  {
    case 0:
      ;
      break;

    case 1: //tube select
      {
        if (OldMode1 != 1)
        {
          NofDiam[1] = 7;
          OldMode1 = 1;
          if (PrintOrNo)
            Serial.println(F("476"));
        }
        else
        {
          if (digitalRead(3) == LOW)
          {
            if (PrintOrNo)
            {
              Serial.print(F("Tube 1 seclected = "));
              Serial.println(NofDiam[1]);
            }
            Mode1 = 15;
          }
          else
          {
            if (NofDiam[1] == 0)
            {
              Mode1 = 16;
              if (PrintOrNo)
              {
                Serial.print(F("Tube 1 seclection failed "));
              }
            }
            else
            {
              NofDiam[1]--;
              if (PrintOrNo)
              {
                Serial.print(F("Tube 1 seclection now DIAM = "));
                Serial.println(NofDiam[1]);
              }
            }


          }

        }
      }
      break;

    case 2: // Head Go Forward
      {
        if (NofStep[1] < 12)
        {
          NofStep[1]++;

        }
        else if (NofStep[1] > 12)
        {
          NofStep[1] = 0;

        }
        else
        {
          Mode1 = 5;


        }
      }  //END case 2
      break;

    case 3: // Return Step Forward
      {

        if (NofStep[1] < 13)
        {
          NofStep[1] = 13;

        }
        else if (NofStep[1] < 15)
        {
          NofStep[1]++;

        }
        else
        {
          Mode1 = 6;


        }
      }  //END case 3
      break;















    case 4: // Head Step Back
      {
        if (NofStep[1] > 12)
        {
          NofStep[1] = 12;

        }
        else if (NofStep[1] > 0)
        {
          NofStep[1]--;

        }
        else
        {
          Mode1 = 9;


        }
      }  //END case 4
      break;

    case 7: // Return Step Forward
      {

        if (NofStep[1] < 13)
        {
          NofStep[1] = 15;

        }
        else if (NofStep[1] > 13)
        {
          NofStep[1]--;

        }
        else
        {
          Mode1 = 8;


        }
      }  //END case 7
      break;

  }













  if (Serial.available() > 0)
  {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);

    byte  tt = Serial.read();
    if (PrintOrNo)
    {
      Serial.print(F("88 tt = "));
      Serial.println(tt);
    }
    switch (tt)  // Main switch of command
    {
      case 86:

      for (byte j86=0;j86<8;j86++)
      {
    digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
         digitalWrite(A4,LOW);
    digitalWrite(A5, LOW);
       digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
delay (50);

 digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
         digitalWrite(A4,LOW);
    digitalWrite(A5, LOW);
       digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      delay (50);

 digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
         digitalWrite(A4,LOW);
    digitalWrite(A5, HIGH);
       digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      delay (50);

 digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
         digitalWrite(A4,LOW);
    digitalWrite(A5, HIGH);
       digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      delay (50);
      
 digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
         digitalWrite(A4,LOW);
    digitalWrite(A5, HIGH);
       digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      delay (50);


 digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
         digitalWrite(A4,HIGH);
    digitalWrite(A5, LOW);
       digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      delay (50);

 digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
         digitalWrite(A4,HIGH);
    digitalWrite(A5, LOW);
       digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      delay (50);

    }

      break;
      case 67:
        {
          Mode0 = 0;
          Mode1 = 0;
          CommandMode = 0;
          NofDiam[0] = 7;
          NofDiam[1] = 7;
          NofStep[0] = 0;
          NofStep[1] = 0;

        }
        break;

      case 69:
        {
          byte tMode0 = Serial.read() - 48;
          tMode0 = tMode0 * 10 + Serial.read() - 48;
          PauseLoop = 10 * int(tMode0);

        }
        break;

      case 79:
        {
          if (PauseLoop < 5000)
            PauseLoop = (PauseLoop * 12) / 10;
        }
        break;

      case 80:
        {
          if (PauseLoop > 100)
            PauseLoop = (PauseLoop * 8) / 10;
        }
        break;


      case 68: // A Back var tubes
        {
          OldCommandMode = CommandMode;
          CommandMode = 68;
          Mode0 = 0;
          Mode1 = 0;
          OldMode0 = 0;
          OldMode1 = 0;

        }// End Back vary tube
        break;



      case 66: // B Back const tube
        {
          OldCommandMode = CommandMode;
          CommandMode = 66;
          Mode0 = 0;
          Mode1 = 0;
        }// End Forward const tube
        break;


      case 70: // F Forward const tube
        {
          OldCommandMode = CommandMode;
          CommandMode = 70;
          Mode0 = 0;
          Mode1 = 0;

        }// End Forward const tube
        break;

      case 85: // U Forward var tubes
        {
          OldCommandMode = CommandMode;
          CommandMode = 85;
          Mode0 = 0;
          Mode1 = 0;
          OldMode0 = 0;
          OldMode1 = 0;

        }// End Forward const tube
        break;



      case 83:  // S Stop
        {
          OldCommandMode = CommandMode;
          CommandMode = 0;
          Mode0 = 0 ;
          Mode1 = 0;
          digitalWrite(13, LOW);

        } // End Stop
        break;



      case 84:  //Begin of T
        {
          Mode0 = 0;
          CommandMode = 0;
          byte tNofDiam = Serial.read() - 48;
          tNofDiam = tNofDiam * 10 + Serial.read() - 48;
          byte tNofStep = Serial.read() - 48;
          tNofStep = 10 * tNofStep + Serial.read() - 48;

          if ((tNofDiam >= NOFTUBEZ) || (tNofStep >= NOFPOINTZ))
          {
            tNofDiam = 0;

            tNofStep = 0;
          }
          if (PrintOrNo)
          {
            Serial.print(F("Set NofDiam "));
            Serial.print(tNofDiam);
            Serial.print(F(" Set NofStep "));
            Serial.println(tNofStep);
          }
          NofDiam[0] = tNofDiam;
          NofStep[0] = tNofStep;
        }
        break;  // End of T

      case 75:  // Begin of K
        {
          Mode1 = 0;
          CommandMode = 0;
          byte tNofDiam = Serial.read() - 48;
          tNofDiam = tNofDiam * 10 + Serial.read() - 48;
          byte tNofStep = Serial.read() - 48;
          tNofStep = 10 * tNofStep + Serial.read() - 48;

          if ((tNofDiam >= NOFTUBEZ) || (tNofStep >= NOFPOINTZ))
          {
            tNofDiam = 0;

            tNofStep = 0;
          }
          if (PrintOrNo)
          {
            Serial.print(F("Set NofDiam 1 "));
            Serial.print(tNofDiam);
            Serial.print(F(" Set NofStep 1 "));
            Serial.println(tNofStep);
          }
          NofDiam[1] = tNofDiam;
          NofStep[1] = tNofStep;
        }
        break; // End of K - second chain



      case 77:
        {
          byte tMode0 = Serial.read() - 48;
          tMode0 = tMode0 * 10 + Serial.read() - 48;

          if (tMode0 < NOFMODES)
          {
            OldMode0 = Mode0;
            Mode0 = tMode0;
            if (PrintOrNo)
            {
              Serial.print(F(" New Mode0 = "));
              Serial.println(Mode0);
            }
          }
          else
          {
            if (PrintOrNo)
            {
              Serial.println(F("Error Mode0 "));
            }
          }
        }
        break;



      case 78:  // N- direct chain 1 command
        {
          byte tMode1 = Serial.read() - 48;
          tMode1 = tMode1 * 10 + Serial.read() - 48;

          if (tMode1 < NOFMODES)
          {
            OldMode1 = Mode1;
            Mode1 = tMode1;
            if (PrintOrNo)
            {
              Serial.print(F(" New Mode1 = "));
              Serial.println(Mode1);
            }
          }
          else
          {
            if (PrintOrNo)
            {
              Serial.println(F("Error Mode1 "));
            }
          }
        } // End of N direct 1 chain command
        break;














      case 91:

        PrintOrNo = 1;
        break;

      case 93:

        PrintOrNo = 0;
        break;


      default:
        if (PrintOrNo)
          Serial.println(F("Default"));
        break;
    }



  }
  else
  {
    if (CommandMode == 0)
    {
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
    }
    else
    {
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
    }


  }
  //if(NofStep[0]++>14)
  //NofStep[0]=0;


  switch (CommandMode)
  {
    case 0:
      {
        if (OldCommandMode != 0)
        {
          Mode0 = 0;

          OldMode0 = 0;
          OldCommandMode = 0;
        }
      }
      break;


    case 66:  // Go Back const tube

      {
        if (OldCommandMode != 66)
        {
          if ( (NofDiam[0] == NofDiam[1]) && ( NofStep[0] == 12 - NofStep[1]))

          {
            Mode0 = 4;
            Mode1 = 2;
            OldCommandMode = 66;
          }
          else
          {

            if (NofDiam[0] != NofDiam[1])
            {


              CommandMode = 0;
              digitalWrite(13, HIGH);

              if (PrintOrNo)
                Serial.println(F("No match Tubes"));


            }

            else if ( NofStep[0] != 12 - NofStep[1])
            {

              Mode0 = 9;
              Mode1 = 5;



              if (PrintOrNo)
                Serial.println(F("No match Steps"));
            }
            //CommandMode = 0;

          }
        }
        else
        {
          if ((Mode0 == 9) && (Mode1 == 5)) // Step is Done
          {


            Mode1 = 3;
          }
          else   if ((Mode0 == 9) && (Mode1 == 6)) // Foots 0 came back
          {

            if (NofStep[1] != 0)
              NofStep[1] = 0;
            else
            {


              Mode0 = 7;

            }

          }
          else   if ((Mode0 == 8) && (Mode1 == 6)) // Foots 0 came back Foots 1 came back
          {
            if (NofStep[0] != 12)
              NofStep[0] = 12;
            else
            {
              //  NofStep[0]=0;
              //  NofStep[1]=12;

              Mode0 = 4;
              Mode1 = 2;
            }
          }




        }
        break;






      }

      break;








    case 70:  // Go Forward const tube
      if (OldCommandMode != 70)
      {
        if ( (NofDiam[0] == NofDiam[1]) && ( NofStep[0] == 12 - NofStep[1]))

        { Mode0 = 2;
          Mode1 = 4;
          OldCommandMode = 70;
        }
        else
        {

          if (NofDiam[0] != NofDiam[1])
          {
            if (Mode1 == 0)
            {
              Mode0 = 1;

            }
            if (Mode0 == 15)
            {
              Mode1 = 1;


            }

            if ((Mode1 == 16) || (Mode0 == 16))
            {
              CommandMode = 0;
              digitalWrite(13, HIGH);
            }
            if (PrintOrNo)
              Serial.println(F("No match Tubes"));


          }

          else if ( NofStep[0] != 12 - NofStep[1])
          {

            if ((NofStep[0] == 0) && (NofStep[1] != 12))
            {
              if (Mode1 == 8)
              {
                NofStep[1] = 12;
              }
              else
                Mode1 = 7;
            }


            if ((Mode0 == 6) && (NofStep[0] != 0))
            {
              NofStep[0] = 0;
            }
            else if ((Mode0 != 6) && (NofStep[0] != 0))
              Mode0 = 3;



            if (PrintOrNo)
              Serial.println(F("No match Steps"));
          }
          //CommandMode = 0;

        }
      }
      else
      {
        if ((Mode0 == 5) && (Mode1 == 9)) // Step is Done
        {


          Mode0 = 3;
        }
        else   if ((Mode0 == 6) && (Mode1 == 9)) // Foots 0 came back
        {
          if (NofStep[0] != 0)
            NofStep[0] = 0;
          else
          {
            Mode1 = 7;

          }
        }
        else   if ((Mode0 == 6) && (Mode1 == 8)) // Foots 0 came back Foots 1 came back
        {
          if (NofStep[1] != 12)
            NofStep[1] = 12;
          else
          {
            //  NofStep[0]=0;
            //  NofStep[1]=12;
            Mode1 = 4;
            Mode0 = 2;

          }
        }


        //else if(Mode0== 6)
        //{
        //OldMode0=Mode0;
        //Mode0 = 2;
        //OldMode0=6;
        //}


      }
      break;











    case 68:  // Go Back variung  tube
      {
        if (OldCommandMode != 68)
        {
          if ( (Mode0 == 0) && (Mode1 == 0))
          {

            Mode1 = 3;
            NofDiam[1] = 7;
          }
          else if ( (Mode0 == 0) && ( Mode1 == 6 ))
          {
            NofStep[1] = 0;

            Mode1 = 1;

          }
          else if ( (Mode0 == 0) && (Mode1 == 15))
          {

            Mode0 = 7;
            NofDiam[0] = 7;

          }
          else if ((Mode0 == 8) && (Mode1 == 15))
          {

            NofStep[0] = 12;
            Mode0 = 1;

          }
          else if ((Mode0 == 15) && (Mode1 == 15))
          {

            Mode0 = 4;
            Mode1 = 2;
            OldCommandMode = 68;
            if (PrintOrNo)
              Serial.println(F("Initial Set is done"));

          }
          else if ((Mode0 == 16 ) || (Mode1 == 16))
          {
            CommandMode = 0;
            digitalWrite(13, HIGH);

          }
          //OldCommandMode=85;


        }
        else  // Steady go when initial is setted
        {
          if ((Mode0 == 9) && (Mode1 == 5)) // Step is Done
          {


            Mode1 = 3;
          }
          else   if ((Mode0 == 9) && (Mode1 == 6)) // Foots 0 came back begin Tube 0 select
          {

            NofStep[1] = 0;

            Mode1 = 1;
            NofDiam[1] = 7;
          }
          else   if ((Mode0 == 9) && (Mode1 == 15)) // Foots 0 came back Foots 1 came back
          {

            Mode0 = 7;


          }

          else   if ((Mode0 == 8) && (Mode1 == 15)) // Foots 0 came back Foots 1 came back
          {

            NofStep[0] = 12;

            Mode0 = 1;
            NofDiam[0] = 7;

          }
          else   if ((Mode0 == 15) && (Mode1 == 15)) // Foots 0 came back Foots 1 came back
          {
            Mode0 = 4;
            Mode1 = 2;


          }



        }
        if ((Mode0 == 16) || (Mode1 == 16))
        {
          CommandMode = 0;
          digitalWrite(13, HIGH);

        }




      }
      break;  // End A go Back various Tubes





























    case 85:  // Go Forward variung  tube
      {
        if (OldCommandMode != 85)
        {
          if ( (Mode0 == 0) && (Mode1 == 0))
          {
            Mode0 = 3;
            NofDiam[0] = 7;
          }
          else if ( (Mode0 == 6) && ( Mode1 == 0 ))
          {
            NofStep[0] = 0;
            // NofDiam[0]=7;
            Mode0 = 1;

          }
          else if ( (Mode0 == 15) && (Mode1 == 0))
          {
            Mode1 = 7;
            NofDiam[1] = 7;

          }
          else if ((Mode0 == 15) && (Mode1 == 8))
          {
            NofStep[1] = 12;
            //NofDiam[1]=7;
            Mode1 = 1;

          }
          else if ((Mode0 == 15) && (Mode1 == 15))
          {

            Mode0 = 2;
            Mode1 = 4;
            OldCommandMode = 85;
            if (PrintOrNo)
              Serial.println(F("Initial Set is done"));

          }
          else if ((Mode0 == 16 ) || (Mode1 == 16))
          {
            CommandMode = 0;
            digitalWrite(13, HIGH);

          }
          //OldCommandMode=85;


        }
        else  // Steady go when initial is setted
        {
          if ((Mode0 == 5) && (Mode1 == 9)) // Step is Done
          {


            Mode0 = 3;
          }
          else   if ((Mode0 == 6) && (Mode1 == 9)) // Foots 0 came back begin Tube 0 select
          {
            if (NofStep[0] != 0)
              NofStep[0] = 0;

            Mode0 = 1;
            NofDiam[0] = 7;
          }
          else   if ((Mode0 == 15) && (Mode1 == 9)) // Foots 0 came back Foots 1 came back
          {

            Mode1 = 7;


          }

          else   if ((Mode0 == 15) && (Mode1 == 8)) // Foots 0 came back Foots 1 came back
          {
            if (NofStep[1] != 12)
              NofStep[1] = 12;

            Mode1 = 1;
            NofDiam[1] = 7;

          }
          else   if ((Mode0 == 15) && (Mode1 == 15)) // Foots 0 came back Foots 1 came back
          {

            Mode1 = 4;
            Mode0 = 2;

          }



        }
        if ((Mode0 == 16) || (Mode1 == 16))
        {
          CommandMode = 0;
          digitalWrite(13, HIGH);

        }




      }
      break;  // End G go Forward various Tubes




  }  // End Switch CommandMode




  // Serial.println(OldMode);













  servo0.write ( Shift[0] + 180 -  Points[0] [NofDiam[0]] [NofStep[0]]);
  servo1.write (Shift[1] + 180 - Points[1] [NofDiam[0]] [NofStep[0]]);
  servo2.write (Shift[2] + (Points[0] [NofDiam[0]] [NofStep[0]]));
  servo3.write (Shift[3] + (Points[1] [NofDiam[0]] [NofStep[0]]));



  servo4.write (Shift[4] + 180 - Points[0] [NofDiam[1]] [NofStep[1]]);
  servo5.write (Shift[5] + 180 - Points[1] [NofDiam[1]] [NofStep[1]]);
  servo6.write (Shift[6] + Points[0] [NofDiam[1]] [NofStep[1]]);
  servo7.write (Shift[7] + Points[1] [NofDiam[1]] [NofStep[1]]);

  //     servo4.write (Shift[4]+Points[0] [NofDiam[1]] [NofStep[1]]);
  //     servo5.write (Shift[5]+Points[1] [NofDiam[1]] [NofStep[1]]);
  //    servo6.write (Shift[6]+180 - Points[0] [NofDiam[1]] [NofStep[1]]);
  //     servo7.write (Shift[7]+180 - Points[1] [NofDiam[1]] [NofStep[1]]);

  //    servo4.write ( Shift[4]+180-  Points[0] [NofDiam[0]] [NofStep[0]]);
  //   servo5.write (Shift[5]+180-Points[1] [NofDiam[0]] [NofStep[0]]);
  // servo6.write (Shift[6]+ (Points[0] [NofDiam[0]] [NofStep[0]]));
  // servo7.write (Shift[7]+ (Points[1] [NofDiam[0]] [NofStep[0]]));



  delay(PauseLoop - 50);


  if (digitalRead(A0) == digitalRead(A1))
  {
    digitalWrite(A0, !digitalRead(A0));

    delay(30);
    digitalWrite(A0, !digitalRead(A0));
    delay(20);
  }
  else
  {
    digitalWrite(A0, !digitalRead(A0));
    digitalWrite(A1, !digitalRead(A1));
    delay(50);
    digitalWrite(A0, !digitalRead(A0));
    digitalWrite(A1, !digitalRead(A1));
  }
  if (PrintOrNo)
  {
    Serial.print(F("649 Mode0 = "));
    Serial.print(Mode0);
    Serial.print(F(" OldMode0 = "));
    Serial.print(OldMode0);

    Serial.print(F(" Mode1 = "));
    Serial.print(Mode1);
    Serial.print(F(" OldMode1 = "));
    Serial.print(OldMode1);



    Serial.print(F(" CommandMode = "));
    Serial.print(CommandMode);
    Serial.print(F(" OldCommandMode = "));
    Serial.print(OldCommandMode);

    Serial.print(F(" NofStep[0] = "));
    Serial.print(NofStep[0]);
    Serial.print(F(" NofDiam[0] = "));
    Serial.print(NofDiam[0]);


    Serial.print(F(" NofStep[1] = "));
    Serial.print(NofStep[1]);
    Serial.print(F(" NofDiam[1] = "));
    Serial.print(NofDiam[1]);
    Serial.print(F(" D0="));
    Serial.print(digitalRead(2));
    Serial.print(F(" D1="));
    Serial.println(digitalRead(3));

  }

  if (Mode1 == 16)
  {
    digitalWrite(A3, digitalRead(A2));
    digitalWrite(A2, !digitalRead(A2));

  }
  else
  {
    if (digitalRead(3) == HIGH)
    {
      digitalWrite(A3, HIGH);
      digitalWrite(A2, LOW);
    }
    else
    {
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
    }

  }



  if (Mode0 == 16)
  {
    digitalWrite(A5, digitalRead(A4));
    digitalWrite(A4, !digitalRead(A4));

  }
  else
  {
    if (digitalRead(2) == HIGH)
    {
      digitalWrite(A5, HIGH);
      digitalWrite(A4, LOW);
    }
    else
    {
      digitalWrite(A4, HIGH);
      digitalWrite(A5, LOW);
    }

  }




}
