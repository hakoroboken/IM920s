#include "zk_api.hpp"

char input[50];
int i = 0;  

void setup() {
  zk_api_v2::setup();

  Serial.begin(115200);
}

void loop() {
  if(zk_api_v2::IM920Serial.available()) 
  {
    input[i] = zk_api_v2::IM920Serial.read();
    if (input[i] == '\n') 
    {
      if(input[0] == 'I')
      {
        for(int j = 0; j <= i; j++)
        {
          input[j] = 0;
        }
        zk_api_v2::control_motor1(0);
        Serial.println("error");
        i = 0;
      }
      else
      {
        String read(input);
        String data = read.substring(11);

        int first_com = data.indexOf(',');
        String x_str = data.substring(0, first_com);
        String non_first = data.substring(first_com+1);

        int second_com = non_first.indexOf(',');
        String y_str = non_first.substring(0, second_com);
        String non_second = non_first.substring(second_com+1);

        int third_com = non_second.indexOf(',');
        String z_str = non_second.substring(0, third_com);
        String non_third = non_second.substring(third_com+1);

        int fourth_com = non_third.indexOf(',');
        String m1_str = non_third.substring(0, fourth_com);
        String non_fourth = non_third.substring(fourth_com+1);

        int fifth_com = non_fourth.indexOf(',');
        String m2_str = non_fourth.substring(0, fifth_com);
        String non_fifth = non_fourth.substring(fifth_com+1);

        float x_hold = x_str.toFloat();
        float y_hold = y_str.toFloat();
        float z_hold = z_str.toFloat();
        float m1_hold = m1_str.toFloat();
        float m2_hold = m2_str.toFloat();

        x_hold = (x_hold - 10) / 10.0 * 255.0;
        int x = (int)x_hold;
        y_hold = (y_hold - 10) / 10.0 * 255.0;
        int y = (int)y_hold;
        z_hold = (z_hold - 10) / 10.0 * 255.0;
        int z = (int)z_hold;
        m1_hold = (m1_hold - 10) / 10.0 * 255.0;
        int m1 = (int)m1_hold;
        m2_hold = (m2_hold - 10) / 10.0 * 255.0;
        int m2 = (int)m2_hold;

        zk_api_v2::control_motor1(x);
        Serial.println(x);

        for(int j = 0; j <= i; j++)
        {
          input[j] = 0;
        }
        i = 0;
      }
    }
    else
    {
        i++;
    }
  }
}