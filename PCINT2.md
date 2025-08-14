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

| Bit  | Name     | Pin   | Description                                 |
|------|----------|--------|---------------------------------------------|
| 0    | PCINT16  | PD0   | Enable pin change interrupt for PD0         |
| 1    | PCINT17  | PD1   | Enable pin change interrupt for PD1         |
| 2    | PCINT18  | PD2   | Enable pin change interrupt for PD2         |
| 3    | PCINT19  | PD3   | Enable pin change interrupt for PD3         |
| 4    | PCINT20  | PD4   | Enable pin change interrupt for PD4         |
| 5    | PCINT21  | PD5   | Enable pin change interrupt for PD5         |
| 6    | PCINT22  | PD6   | Enable pin change interrupt for PD6         |
| 7    | PCINT23  | PD7   | Enable pin change interrupt for PD7         |

### **Enable Interrupts for Port D Pins (Examples)**

```c
bitSet(PCMSK2, PCINT16); // Enable interrupt for PD0
bitSet(PCMSK2, PCINT17); // Enable interrupt for PD1
bitSet(PCMSK2, PCINT18); // Enable interrupt for PD2
bitSet(PCMSK2, PCINT19); // Enable interrupt for PD3
bitSet(PCMSK2, PCINT20); // Enable interrupt for PD4
bitSet(PCMSK2, PCINT21); // Enable interrupt for PD5
bitSet(PCMSK2, PCINT22); // Enable interrupt for PD6
bitSet(PCMSK2, PCINT23); // Enable interrupt for PD7
```

You can enable multiple pins simultaneously by setting multiple bits.
```c
PCMSK2 |= (1 << PCINT18) | (1 << PCINT20); // Enable PD2 and PD4
```
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

ISR(PCINT2_vect) 
{
    if (bitCheckHigh(PIND, 4)) 
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
