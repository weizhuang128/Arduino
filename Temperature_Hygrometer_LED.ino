//www.elegoo.com
//2016.12.9

#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup()
{
  lcd.begin(16, 2);
    Serial.begin( 9600);
}


static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );



/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}





void loop()
{


  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( " %" );
  }


  lcd.setCursor(0, 0);
  lcd.print("Humidity ");
  lcd.print(humidity,1);
  lcd.print( "%" );

    lcd.setCursor(0,2);
    lcd.print("Temp ");
    lcd.print(temperature,1);
    lcd.print(" deg. C");
  //delay(1);
}
