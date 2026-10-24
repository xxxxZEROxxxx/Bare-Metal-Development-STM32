# ADC
#### Note, and to configure a ADC for one time conversion
1. you do not configure GPIO to AF for ADC pin, analog pins require you to set the GPIO mode directly to Analog Mode (MODER = 11), to find it, look for DS pin definitions, in the Additional functions

```c++

void adc_init(void) {
    // ENABLE CLOCK TREE / GPIOA IN AHB1, ADC IN APB2
    // GPIO WILL BE ENABLED LATER IN FUNCTION CALL
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // GPIO ENABLE AND SET TO ANALOGE
    gpio_init(GPIOA, 1, AN);

    // ADC CONFIGURE
    /**  use single conversion mode, set CONT to 0 in CR2
     *  then set the order and channel in the SQRx
     *  default 12bit resolution
     *  SAMPLE TIME 28 CYCLES : SMPRx -> 010
     */
    ADC1->CR2 &= ~CR2_CONT; // SET CONT TO 0
    ADC1->SMPR2 |= ADC_SMPR; //SET SAMPLE TIME
    ADC1->SQR1 &= ~(ADC_SQR_L); // SET TOTAL CONVERSION NUMBER TO 1
    ADC1->SQR3 |= SQR_FIRST; // SET THE FIRST CONVERSION TO CHANNEL 1

    ADC1->CR2 |= ADON; // TURN ON ADC
}
```


## ADC Modes
| MODE                  | Function                                                                                                                                                                                     | Set                                                                                                                                                                                                                          |
|-----------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|Single conversion mode| the ADC performs a single conversion of the selected channel and then stops. This mode is useful for applications where periodic or event-driven sampling of an analog signal is required    | set the CONT bit to 0 in the ADC_CR2 register                                                                                                                                                                                |
|Continuous conversion mode| This mode allows the ADC to repeatedly convert the input signal. After each conversion, the next conversion starts automatically.                                                            | setting the CONT bit to 1 in the ADC_CR2 register                                                                                                                                                                            |
|Scan mode| This mode is used to convert a sequence of analog channels. We use this mode when we need to sample multiple signals in a defined order.                                                     | enabled by settingthe SCAN bit in the ADC_CR1 register and then configuring the sequence of channels in the ADC_SQRx registers. If the CONT bit is set in ADC_CR2, the sequence restarts after the last channel is converted |
|Discontinuous mode| allows us to convert a subset of channels within a sequence. It reduces the number of channels converted in each sequence, which can be useful for power saving or reducing processing load. | enabled by setting the DISCEN bit in the ADC_CR1 register and then defining the number of channels to convert in each group by setting the DISCNUM bits in the ADC_CR1 register.                                             |
|Injected conversion mode| This mode is designed for higher-priority conversions that can interrupt regular conversions and is useful for applications that require precise timing for specific signal measurements.    | configuring the injected channels and their sequence in the ADC_JSQR register, and then starting the conversion by setting the JSWSTART bit in the ADC_CR2 register or via an external trigger.                              |









## EXPLAIN TO PARAMETERS
#### Sampling speed
#### Resolution
eg a 8 bit resolution can store 255 interval between 0~VREF, usually VREF is 3.6V max, so resolution is 255, same for others like 32bit, 12bit
#### Step size
like 8bit resolution, have 255 interval, so step size is (VREF-0)/255, like 0.2mV stuff
#### Multiplexing ADC channels
having 13 adc channels does not means each channel have a seperate and listening, actually they connect to MUX, like this

![mux.png](IMG/mux.png)

