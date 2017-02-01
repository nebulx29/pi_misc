import com.pi4j.io.gpio.*;

class HelloPi4J {
	public static final GpioController gpio = GpioFactory.getInstance();

	public static void main(String[] args) {
		try {
			GpioPinDigitalOutput led = gpio.provisionDigitalOutputPin(RaspiPin.GPIO_06);
			led.setShutdownOptions(true, PinState.LOW);
			//led.setState(PinState.HIGH);
			led.blink(100,20000); // blink for 10sec
			Thread.sleep(20000);
			led.setState(PinState.LOW);
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
		}
		gpio.shutdown();
	}

}
