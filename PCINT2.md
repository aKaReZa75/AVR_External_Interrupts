This document covers the configuration and usage of Pin Change Interrupt 2 (PCINT2) on the ATmega328 microcontroller. It explains how to enable interrupts for pins PD0–PD7 using PCICR and PCMSK2, how to clear the PCIF2 flag, write the ISR, and apply it in practical applications.

---

## **PCINT2 Overview**

| Group     | Pins     | Port     | Interrupt Vector |
|-----------|----------|----------|------------------|
| PCINT2    | PD0–PD7  | PORTD    | `PCINT2_vect`    |

Pin Change Interrupt 2 monitors all pins on PORTD. Any logical change (rising or falling edge) on an enabled pin will trigger the interrupt.

---

## **PCICR – Pin Change Interrupt Control Register**

| Bit | Name   | Description                          |
|-----|--------|--------------------------------------|
| 2   | PCIE2  | Enable Pin Change Interrupt for PCINT2 group |

### **Enable PCINT2 Group:**

```c
bitSet(PCICR, PCIE2); // Enable pin change interrupt for PORTD (PCINT2 group)
```

---

## **PCMSK2 – Pin Change Mask Register 2**

| Bit | Name     | Pin | Description                        |
|-----|----------|-----|------------------------------------|
| 0–7 | PCINT16–23 | PD0–PD7 | Enable interrupt for specific pin |

### **Enable Interrupt for PD4 (Example):**

```c
bitSet(PCMSK2, PCINT20); // Enable pin change interrupt for PD4
```

You can enable multiple pins simultaneously by setting multiple bits.

---

## **PCIFR – Pin Change Interrupt Flag Register**

| Bit | Name   | Description                          |
|-----|--------|--------------------------------------|
| 2   | PCIF2  | Pin Change Interrupt Flag for PCINT2 |

### **Clear PCINT2 Flag Manually:**

```c
intFlag_clear(PCIFR, PCIF2); // Clear PCINT2 interrupt flag
```

> [!NOTE]
> The flag is automatically cleared when the ISR is executed.

---

## **Writing the ISR for PCINT2**

The ISR is triggered on any logical change of enabled pins in PORTD. You must read the current pin state and compare it to the previous state to detect rising or falling edges.

### **Example ISR:**

```c
volatile uint8_t lastPinD;

ISR(PCINT2_vect) 
{
    uint8_t currentPinD = PIND;
    uint8_t changedPins = currentPinD ^ lastPinD;

    if (bitCheckHigh(currentPinD, PD4)) 
    {
        // Rising edge on PD4
    } 
    else 
    {
        // Falling edge on PD4
    }
}
```

---

## **Complete Initialization Example**

```c
void pcint2_Init(void) 
{
    GPIO_Config_INPUT(DDRD, PD4);     // Configure PD4 as input
    bitSet(PCICR, PCIE2);             // Enable PCINT2 group
    bitSet(PCMSK2, PCINT20);          // Enable interrupt for PD4
    globalInt_Enable;                 // Enable global interrupts
}
```

---

## **Practical Applications**

| Application            | Description                                      |
|------------------------|--------------------------------------------------|
| Keypad scanning        | Detect key presses on PORTD pins                |
| UART RX edge detection | Monitor RX line for activity                    |
| External module sync   | React to signals from external digital modules  |
| Wake-up from sleep     | Use pin change to wake MCU from low-power mode  |

---

## **Summary of PCINT2 Setup**

| Step                        | Register | Action                                  |
|-----------------------------|----------|-----------------------------------------|
| Configure PDx as input      | DDRD     | `GPIO_Config_INPUT(DDRD, PDx)`          |
| Enable PCINTx in mask       | PCMSK2   | Set `PCINTx` bit                        |
| Enable PCINT2 group         | PCICR    | Set `PCIE2` bit                         |
| Enable global interrupts    | SREG     | Set `SREG_I` bit                        |
| Write ISR                   | PCINT2_vect | Detect and handle pin changes         |

> [!CAUTION]
> Pin change interrupts are edge-agnostic. You must track previous pin states to determine rising or falling edges.



# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
