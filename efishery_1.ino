#define btn_send_data   13
#define max_data        4

uint8_t *convert_to_array(uint32_t data, uint8_t flag);
void printHex(int num, int precision);

uint8_t data_bank[max_data];
uint8_t temp;

void setup() {
  // put your setup code here, to run once:
  pinMode(btn_send_data, INPUT);
  digitalWrite(btn_send_data, HIGH);
  Serial.begin(9600);
  Serial.println("Please press button to print data !");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btn_send_data) == LOW)
  {
    for (uint8_t i=0; i<max_data; i++)
    {
      data_bank[i] = (*convert_to_array(0x12345678, i)); //for example 0x12345678
      printHex(data_bank[i], 2);    //print data with hex format
      Serial.print(" ");
    }
    Serial.println();
    delay(1000);
  }
}

uint8_t *convert_to_array(uint32_t data, uint8_t flag)
{
  switch(flag)
  {
    case 0: temp = (uint32_t) (data>>24); break;
    case 1: temp = (uint32_t) (data>>16); break;
    case 2: temp = (uint32_t) (data>>8); break;
    case 3: temp = (uint32_t) (data); break;
    default: temp = 0xFF; break;
  }
  return &temp;
}

void printHex(int num, int precision) {
     char tmp[16];
     char format[128];

     sprintf(format, "0x%%.%dX", precision);

     sprintf(tmp, format, num);
     Serial.print(tmp);
}

