/* Simple code for steering 2-wheel robot based on Romeo board using Bluetooth app
created by Jacek Bera */

//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
  
///For previous Romeo, please use these pins
//int E1 = 6;     //M1 Speed Control
//int E2 = 9;     //M2 Speed Control
//int M1 = 7;    //M1 Direction Control
//int M2 = 8;    //M1 Direction Control

int x = 100;
  
//Stop
void stop(void)                    		
{
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);    
} 

//Move forward
void advance(char a,char b)          	
{
//PWM Speed Control
  analogWrite (E1,a);      				
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}  

//Move backward
void back_off (char a,char b)          	
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

//Turn Left
void turn_L (char a,char b)             
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}

//Turn Right
void turn_R (char a,char b)             
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

void faster()
{
  x=x+15;
}

void slower()
{
  x=x-15;
}


void setup(void) 
{ 
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);  
//Set Baud Rate
  Serial.begin(115200);      			
} 
void loop(void) 
{
  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
	  
//Move Forward
      case 'U':
// Move forward in max speed
        advance (x,x);   				
        break;
//Move Backward
      case 's':
// Move back in max speed
        back_off (x,x);   				
        break;
//Turn Left
      case 'L':
        turn_L (150,150);
        break; 
//Turn Right		
      case 'R':
        turn_R (150,150);
        break;
      case '+':
        faster();
        Serial.println(x);
        advance (x,x);
        break;
      case '-':
        slower();
        Serial.println(x);
        advance (x,x);
        break;
      case 'x':
        stop();
        break;
      }
    }
    else stop();  
  }
}
