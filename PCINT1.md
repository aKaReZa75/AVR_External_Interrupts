This document covers the configuration and usage of Pin Change Interrupt 1 (PCINT1) on the ATmega328 microcontroller. It explains how to enable interrupts for pins PC0–PC6 using PCICR and PCMSK1, how to clear the PCIF1 flag, write the ISR, and implement logic to detect pin changes.

---

## **PCINT1 Overview**

| Group     | Pins     | Port     | Interrupt Vector |
|-----------|----------|----------|------------------|
| PCINT1    | PC0–PC6  | PORTC    | `PCINT1_vect`    |

Pin Change Interrupt 1 monitors all pins on PORTC. Any logical change (rising or falling edge) on an enabled pin will trigger the interrupt.

---

## **PCICR – Pin Change Interrupt Control Register**

| Bit | Name   | Description                          |
|-----|--------|--------------------------------------|
| 1   | PCIE1  | Enable Pin Change Interrupt for PCINT1 group |

### **Enable PCINT1 Group:**

```c
bitSet(PCICR, PCIE1); // Enable pin change interrupt for PORTC (PCINT1 group)
```

---

## **PCMSK1 – Pin Change Mask Register 1**

| Bit | Name    | Pin | Description                        |
|-----|---------|-----|------------------------------------|
| 0–6 | PCINT8–14 | PC0–PC6 | Enable interrupt for specific pin |

### **Enable Interrupt for PC2 (Example):**

```c
bitSet(PCMSK1, PCINT10); // Enable pin change interrupt for PC2
```

You can enable multiple pins simultaneously by setting multiple bits.

---

## **PCIFR – Pin Change Interrupt Flag Register**

| Bit | Name   | Description                          |
|-----|--------|--------------------------------------|
| 1   | PCIF1  | Pin Change Interrupt Flag for PCINT1 |

### **Clear PCINT1 Flag Manually:**

```c
intFlag_clear(PCIFR, PCIF1); // Clear PCINT1 interrupt flag
```

> [!NOTE]
> The flag is automatically cleared when the ISR is executed.

---

## **Writing the ISR for PCINT1**

The ISR is triggered on any logical change of enabled pins in PORTC. You must read the current pin state and compare it to the previous state to detect rising or falling edges.

### **Example ISR:**

```c
volatile uint8_t lastPinC;

ISR(PCINT1_vect) 
{
    if (bitCheckHigh(currentPinC, PC2)) 
    {
        // Rising edge on PC2
    } 
    else 
    {
        // Falling edge on PC2
    }
}
```

---

## **Complete Initialization Example**

```c
void pcint1_Init(void) 
{
    GPIO_Config_INPUT(DDRC, PC2);     // Configure PC2 as input
    bitSet(PCICR, PCIE1);             // Enable PCINT1 group
    bitSet(PCMSK1, PCINT10);          // Enable interrupt for PC2
    globalInt_Enable;                 // Enable global interrupts
}
```

---

## **Typical Use Cases**

| Application            | Description                                      |
|------------------------|--------------------------------------------------|
| Capacitive touch input | Detect changes on sensor pads connected to PCx  |
| I2C or analog event sync| Monitor external signal transitions             |
| Wake-up from sleep     | Use pin change to wake MCU from low-power mode   |
| Multi-channel input     | Monitor multiple digital inputs simultaneously  |

---

## **Summary of PCINT1 Setup**

| Step                        | Register | Action                                  |
|-----------------------------|----------|-----------------------------------------|
| Configure PCx as input      | DDRC     | `GPIO_Config_INPUT(DDRC, PCx)`          |
| Enable PCINTx in mask       | PCMSK1   | Set `PCINTx` bit                        |
| Enable PCINT1 group         | PCICR    | Set `PCIE1` bit                         |
| Enable global interrupts    | SREG     | Set `SREG_I` bit                        |
| Write ISR                   | PCINT1_vect | Detect and handle pin changes         |

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
