# External Interrupts in ATMEGA328

External interrupts in microcontrollers like the ATMEGA328 are used to trigger an interrupt based on external events such as a button press or a signal change. These interrupts are useful for responding to events asynchronously, which allows the main program to continue running while it waits for an interrupt to occur. The ATMEGA328 has several external interrupt pins (INT0, INT1) that can be configured to trigger interrupts on specific events like a rising edge, falling edge, or any logical change on the input signal.

> [!CAUTION]
> It is absolutely critical that you carefully read every single word of this document, line by line, to ensure you don't miss any details. Nothing can be overlooked.

> [!TIP]
> If you're looking to better understand how to navigate and use my GitHub repositories — including exploring their structure, downloading or cloning projects, submitting issues, and asking questions 
> everything you need is clearly explained in this video:  
> [aKaReZa 95 - Programming, Git - PART B](https://youtu.be/zYiUItVFRqQ)   
> Make sure to check it out!

## Registers & Bit Descriptions

The external interrupt configuration and control are managed by specific registers in the ATMEGA328. Here are the main registers involved:

### 1. EIMSK (External Interrupt Mask Register)
This register controls the enabling and disabling of external interrupts.

| Bit   | Name  | Description                               |
|-------|-------|-------------------------------------------|
| 0     | INT0  | Enable external interrupt on INT0 pin     |
| 1     | INT1  | Enable external interrupt on INT1 pin     |

#### Example:
> [!NOTE]  
> The macros used in the code below are all defined in the `aKaReZa.h` header file, and detailed descriptions of these macros can be found at the following link:  
> [https://github.com/aKaReZa75/AVR/blob/main/Macros.md](https://github.com/aKaReZa75/AVR/blob/main/Macros.md)

```c
/* Enable external interrupt on INT0 */
bitSet(EIMSK, INT0);

/* Enable external interrupt on INT1 */
bitSet(EIMSK, INT1);
```

### 2. EICRA (External Interrupt Control Register A)
This register controls the trigger conditions for external interrupts (rising, falling, or any logical change).

| Bit   | Name   | Description                                       |
|-------|--------|---------------------------------------------------|
| 0     | ISC00   | Interrupt 0 Sense Control Bit 0 (Rising/Falling)  |
| 1     | ISC01   | Interrupt 0 Sense Control Bit 1 (Rising/Falling)  |
| 2     | ISC10   | Interrupt 1 Sense Control Bit 0 (Rising/Falling)  |
| 3     | ISC11   | Interrupt 1 Sense Control Bit 1 (Rising/Falling)  |

- ISC00 and ISC01 control the sense level for INT0.
- ISC10 and ISC11 control the sense level for INT1.

#### INTx Trigger Conditions (ISCx0, ISCx1):
1. **Low Level (ISCx0 = 0, ISCx1 = 0)**:  
   - The interrupt will trigger when the external pin INTx is at a low level (0V).
   - This is used when you want to trigger an interrupt for a constant low signal.

2. **Any Logical Change (ISCx0 = 1, ISCx1 = 0)**:  
   - The interrupt will trigger on any logical change of the INTx pin (from high to low or low to high).
   - This is useful for detecting any changes in state.

3. **Falling Edge (ISCx0 = 0, ISCx1 = 1)**:  
   - The interrupt will trigger when the INTx pin transitions from high to low.
   - This is often used to detect events like a button press when it is connected to ground.

4. **Rising Edge (ISCx0 = 1, ISCx1 = 1)**:  
   - The interrupt will trigger when the INTx pin transitions from low to high.
   - This is often used to detect events like a button release when the pin is pulled high.

#### Example:
```c
/* Set INT0 to trigger on rising edge */
bitSet(EICRA, ISC00);
bitSet(EICRA, ISC01);

/* Set INT1 to trigger on falling edge */
bitClear(EICRA, ISC10);
bitSet(EICRA, ISC11);
```

### 3. EIFR (External Interrupt Flag Register)
This register is used to monitor the interrupt flags for external interrupts.

| Bit   | Name  | Description                           |
|-------|-------|---------------------------------------|
| 0     | INTF0 | External Interrupt Flag 0             |
| 1     | INTF1 | External Interrupt Flag 1             |

#### Example:
```c
/* Check if the external interrupt on INT0 occurred */
if (bitCheckHigh(EIFR, INTF0)) 
{
    /* Handle interrupt */
    bitSet(EIFR, INTF0);  // Clear the interrupt flag
}
```

## Example Code
Below is an example of setting up external interrupts on INT0 and INT1 pins.

```c
#include "aKaReZa.h"

/* External interrupt service routine for INT0 */
ISR(INT0_vect) 
{
    /* Handle the interrupt triggered on INT0 */
    /* Code to handle the interrupt */
}

/* External interrupt service routine for INT1 */
ISR(INT1_vect) 
{
    /* Handle the interrupt triggered on INT1 */
    /* Code to handle the interrupt */
}

int main(void) 
{
    /* Set INT0 to trigger on rising edge */
    bitSet(EICRA, ISC00);
    bitSet(EICRA, ISC01);

    /* Set INT1 to trigger on falling edge */
    bitClear(EICRA, ISC10);
    bitSet(EICRA, ISC11);

    /* Enable external interrupts for INT0 and INT1 */
    bitSet(EIMSK, INT0);
    bitSet(EIMSK, INT1);
    
    /* Global interrupt enable */
    globalInt_Enable;
    
    while(1)
    {
        /* Main program running, interrupts will be handled asynchronously */
    }
}
```

## Pin Change Interrupts

Pin Change Interrupts are a feature in microcontrollers that allow interrupts to be triggered based on changes (rising or falling edge) on specific pins, which are not necessarily part of the external interrupt pins. The ATMEGA328 has a set of Pin Change Interrupts that can be used to detect changes on general-purpose I/O pins. This is useful when you want to monitor signals on pins that are not directly connected to external interrupt lines.

In the ATMEGA328, the Pin Change Interrupts can be triggered on pins PD0 to PD7 (for Port D), PB0 to PB7 (for Port B), and PC0 to PC5 (for Port C). The configuration of these interrupts is controlled through a set of registers.

#### Key Registers for Pin Change Interrupts

1. **PCICR (Pin Change Interrupt Control Register)**
   This register enables or disables Pin Change Interrupts for each port (Port B, Port C, and Port D).

| Bit   | Name     | Description                                  |
|-------|----------|----------------------------------------------|
| 0     | PCIE0    | Enable Pin Change Interrupt for Port B       |
| 1     | PCIE1    | Enable Pin Change Interrupt for Port C       |
| 2     | PCIE2    | Enable Pin Change Interrupt for Port D       |

#### Example:
```c
/* Enable Pin Change Interrupt for Port D */
bitSet(PCICR, PCIE2);

/* Enable Pin Change Interrupt for Port B */
bitSet(PCICR, PCIE0);
```

2. **PCMSK (Pin Change Mask Register)**
   These registers control which individual pins within each port can trigger interrupts.

- **PCMSK0 (Pin Change Mask Register for Port B)**
- **PCMSK1 (Pin Change Mask Register for Port C)**
- **PCMSK2 (Pin Change Mask Register for Port D)**

Each bit in these registers corresponds to a pin on the respective port. When a bit is set to 1, the corresponding pin will generate an interrupt on a state change (rising or falling edge).

| Bit   | Pin   | Description                           |
|-------|-------|---------------------------------------|
| 0     | PCINT0 | Pin Change Interrupt for Pin 0        |
| 1     | PCINT1 | Pin Change Interrupt for Pin 1        |
| 2     | PCINT2 | Pin Change Interrupt for Pin 2        |
| 3     | PCINT3 | Pin Change Interrupt for Pin 3        |
| 4     | PCINT4 | Pin Change Interrupt for Pin 4        |
| ...   | ...   | ...                                   |

#### Example:
```c
/* Enable Pin Change Interrupt for Pin 2 on Port D */
bitSet(PCMSK2, PCINT2);

/* Enable Pin Change Interrupt for Pin 1 on Port B */
bitSet(PCMSK0, PCINT1);
```

3. **PCIFR (Pin Change Interrupt Flag Register)**
   This register contains the flags that indicate whether a pin change interrupt has occurred. Each bit corresponds to a port (Port B, Port C, and Port D). Writing a `1` to a flag bit clears it.

| Bit   | Name    | Description                         |
|-------|---------|-------------------------------------|
| 0     | PCIF0   | Pin Change Interrupt Flag for Port B|
| 1     | PCIF1   | Pin Change Interrupt Flag for Port C|
| 2     | PCIF2   | Pin Change Interrupt Flag for Port D|

#### Example:
```c
/* Check if a Pin Change Interrupt occurred on Port D */
if (bitCheckHigh(PCIFR, PCIF2)) 
{
    /* Handle interrupt */
    bitSet(PCIFR, PCIF2);  // Clear the interrupt flag
}
```

#### Example Code to Configure Pin Change Interrupts

```c
#include "aKaReZa.h"

/* Pin Change Interrupt service routine for Port D */
ISR(PCINT2_vect) 
{
    /* Handle the interrupt triggered by a pin change on Port D */
    /* Code to handle the interrupt */
}

/* Pin Change Interrupt service routine for Port B */
ISR(PCINT0_vect) 
{
    /* Handle the interrupt triggered by a pin change on Port B */
    /* Code to handle the interrupt */
}

int main(void) 
{
    /* Enable Pin Change Interrupt for Port D */
    bitSet(PCICR, PCIE2);

    /* Enable Pin Change Interrupt for Pin 3 on Port D */
    bitSet(PCMSK2, PCINT3);

    /* Enable Pin Change Interrupt for Port B */
    bitSet(PCICR, PCIE0);

    /* Enable Pin Change Interrupt for Pin 1 on Port B */
    bitSet(PCMSK0, PCINT1);

    /* Enable global interrupts */
    globalInt_Enable();

    while(1) 
    {
        /* Main program running, pin change interrupts will be handled asynchronously */
    }    
}
```

## API Reference

This section provides a structured overview of the API functions and Interrupt Service Routines (ISRs) for managing external interrupts on the ATMEGA328 microcontroller. Each function in this section must be called to initialize or deinitialize the corresponding interrupt functionality. The functions allow for setting up the interrupt pins, enabling/disabling interrupts, and configuring trigger conditions.

> [!NOTE]  
> The library and all of its APIs provided below have been developed by myself.  
This library utilizes various macros defined in the `aKaReZa.h` header file, which are designed to simplify bitwise operations and register manipulations.    
Detailed descriptions of these macros can be found at the following link:  
> [https://github.com/aKaReZa75/AVR/blob/main/Macros.md](https://github.com/aKaReZa75/AVR/blob/main/Macros.md)  

> [!CAUTION]
Always ensure that global interrupts are enabled using the `sei()` function. Without enabling global interrupts, the microcontroller will not respond to any interrupt triggers.  
The `sei()` function sets the Global Interrupt Flag (I-bit) in the Status Register (SREG), which allows interrupt requests to be processed by the microcontroller.

You can use the following macros to enable and disable global interrupts:

- **`globalInt_Enable`**: This macro is equivalent to calling `sei()`. It enables global interrupts, allowing the microcontroller to respond to interrupt requests.

- **`globalInt_Disable`**: This macro is equivalent to calling `cli()`. It disables global interrupts, preventing the microcontroller from processing any interrupts.

---

### **External Interrupt 0 (INT0)**
```c
void eINT0_Init(bool _initStatus);
```
* Initializes the External Interrupt 0 (INT0).
* This function configures the interrupt source, sets trigger conditions, and enables/disables the interrupt based on the provided status.
* @param `_initStatus`: 
  - If `_initStatus` is set to `Initialize`, the INT0 interrupt will be configured and enabled.
  - If `_initStatus` is set to `deInitialize`, the INT0 interrupt will be disabled and deinitialized.

#### **Interrupt Service Routine (ISR):**
```c
ISR(INT0_vect)
{
  /* Place your code here */    
}
```

This ISR is triggered when an external interrupt occurs on INT0. The interrupt flag for INT0 is cleared to allow subsequent interrupts.

**Example:**
```c
#include "aKaReZa.h"
#include "eInterrupt.h"

ISR(INT0_vect)
{
  /* Place your code here */

  intFlag_clear(EIFR, INTF0);  /**< Clear the interrupt flag for INT0 to allow further interrupts */
};

int main(void) 
{
    eINT0_Init(Initialize); /**< Initialize External Interrupt 0 (INT0) */
    while(1)
    {
        /* Main program logic */
    };
};
```

---

### **External Interrupt 1 (INT1)**

```c
void eINT1_Init(bool _initStatus);
```
* Initializes the External Interrupt 1 (INT1).
* This function configures the interrupt source, sets trigger conditions, and enables/disables the interrupt based on the provided status.
* @param `_initStatus`: 
  - If `_initStatus` is set to `Initialize`, the INT1 interrupt will be configured and enabled.
  - If `_initStatus` is set to `deInitialize`, the INT1 interrupt will be disabled and deinitialized.

#### **Interrupt Service Routine (ISR):**
```c
ISR(INT1_vect)
{
  /* Place your code here */
};
```

**Example:**
```c
#include "aKaReZa.h"
#include "eInterrupt.h"

/* Interrupt Service Routine for INT1 (External Interrupt 1) */
ISR(INT1_vect)
{
  /* Place your code here */

  intFlag_clear(EIFR, INTF1);  /**< Clear the interrupt flag for INT1 to allow further interrupts */
};

int main(void) 
{
    eINT1_Init(Initialize); /**< Initialize External Interrupt 1 (INT1) */
    while(1)
    {
        /* Main program logic */
    };
};
```

This ISR is triggered when an external interrupt occurs on INT1. The interrupt flag for INT1 is cleared to allow subsequent interrupts.

---

### **Pin Change Interrupt 0 (PCINT0)**

```c
void pcINT0_Init(bool _initStatus);
```
* Initializes the Pin Change Interrupt 0 (PCINT0).
* This function configures the interrupt source and enables/disables the interrupt based on the provided status.
* @param `_initStatus`: 
  - If `_initStatus` is set to `Initialize`, the PCINT0 interrupt will be configured and enabled.
  - If `_initStatus` is set to `deInitialize`, the PCINT0 interrupt will be disabled and deinitialized.

#### **Interrupt Service Routine (ISR):**
```c
ISR(PCINT0_vect) 
{
  /* Place your code here */
};
```

**Example:**
```c
#include "aKaReZa.h"
#include "eInterrupt.h"

/* Interrupt Service Routine for Pin Change Interrupt 0 (PCINT0)*/
ISR(PCINT0_vect) 
{
  /* Place your code here */

  intFlag_clear(PCIFR, PCIE0);  /**< Clear the interrupt flag for PCINT0 to allow further interrupts */
};

int main(void) 
{
    pcINT0_Init(Initialize); /**< Initialize Pin Change Interrupt 0 (PCINT0) */
    while(1)
    {
        /* Main program logic */
    };
};
```
This ISR is triggered when a pin change interrupt occurs on the configured PCINT0 pin. The interrupt flag for PCINT0 is cleared to allow subsequent interrupts.

### Summary of API Functions

| API Function         | Description                                      |
|----------------------|--------------------------------------------------|
| `eINT0_Init`         | Initializes External Interrupt 0 (INT0).         |
| `eINT1_Init`         | Initializes External Interrupt 1 (INT1).         |
| `pcINT0_Init`        | Initializes Pin Change Interrupt 0 (PCINT0).    |

By following these APIs and ISRs, you can effectively handle and manage external interrupts on the ATMEGA328 microcontroller. Each interrupt type requires specific configuration and an ISR to handle the interrupt once triggered.

## Additional Considerations and Common Mistakes

1. **Debouncing Issues**: When using external interrupts triggered by mechanical switches, debounce logic may be necessary to prevent multiple interrupts from being triggered by a single press.
   
   - **Solution**: Use a small delay or software debounce mechanism to ensure clean interrupts.

2. **Interrupt Priority**: ATMEGA328 has fixed interrupt priority, and external interrupts are not the highest priority interrupts. Make sure to handle time-critical tasks in your code accordingly.

3. **Interrupt Flags**: It's essential to clear the interrupt flag (via writing `1` to the flag bit in `EIFR`) in the ISR to ensure that the interrupt can be processed again in the future.

> [!CAUTION]
Always ensure that global interrupts are enabled using the `sei()` function. Without enabling global interrupts, the microcontroller will not respond to any interrupt triggers, including external interrupts or timer interrupts. The `sei()` function sets the Global Interrupt Flag (I-bit) in the Status Register (SREG), which allows interrupt requests to be processed by the microcontroller.

You can use the following macros to enable and disable global interrupts:

- **`globalInt_Enable`**: This macro is equivalent to calling `sei()`. It enables global interrupts, allowing the microcontroller to respond to interrupt requests.

- **`globalInt_Disable`**: This macro is equivalent to calling `cli()`. It disables global interrupts, preventing the microcontroller from processing any interrupts.

By following these steps and considerations, external interrupts can be effectively managed in the ATMEGA328, providing a robust way to handle asynchronous events.

# 🔗 Resources
  Here you'll find a collection of useful links and videos related to the topic of AVR microcontrollers.  

<table style="border-collapse: collapse;">
  <tr>
    <td valign="top" style="padding: 0 10px;">
      <h3 style="margin: 0;">
        <a href="https://youtu.be/eGV7mYVpWX4">aKaReZa 55 – AVR, External Interrupts</a>
      </h3>
      <p style="margin: 8px 0 0;">
        Learn how to set up and use external interrupts on AVR microcontrollers, specifically focusing on the ATMEGA328. Understand interrupt flags and when to manually clear them.
      </p>
    </td>
    <td width="360" valign="top" style="padding: 0;">
      <a href="https://youtu.be/eGV7mYVpWX4">
        <img src="https://img.youtube.com/vi/eGV7mYVpWX4/maxresdefault.jpg"
             width="360"
             alt="aKaReZa 55 – AVR, External Interrupts Thumbnail"/>
      </a>
    </td>
  </tr>
</table>

> [!TIP]
> The resources are detailed in the sections below.  
> To access any of them, simply click on the corresponding blue link.

- [AVR Microntroller](https://github.com/aKaReZa75/AVR)
  ---  
    This repository contains comprehensive resources for AVR microcontrollers, including hardware schematics, software libraries, and educational projects.

# 💻 How to Use Git and GitHub
To access the repository files and save them on your computer, there are two methods available:
1. **Using Git Bash and Cloning the Repository**
   - This method is more suitable for advanced users and those familiar with command-line tools.
   - By using this method, you can easily receive updates for the repository.

2. **Downloading the Repository as a ZIP file**
   - This method is simpler and suitable for users who are not comfortable with command-line tools.
   - Note that with this method, you will not automatically receive updates for the repository and will need to manually download any new updates.

## Clone using the URL.
First, open **Git Bash** :
-  Open the folder in **File Explorer** where you want the library to be stored.
-  **Right-click** inside the folder and select the option **"Open Git Bash here"** to open **Git Bash** in that directory.

![open Git Bash](Images/Step0.png)

> [!NOTE] 
> If you do not see the "Open Git Bash here" option, it means that Git is not installed on your system.  
> You can download and install Git from [this link](https://git-scm.com/downloads).  
> For a tutorial on how to install and use Git, check out [this video](https://youtu.be/BsykgHpmUt8).
  
-  Once **Git Bash** is open, run the following command to clone the repository:

 ```bash
git clone https://github.com/aKaReZa75/AVR_External_Interrupts.git
```
- You can copy the above command by either:
- Clicking on the **Copy** button on the right of the command.
- Or select the command text manually and press **Ctrl + C** to copy.
- To paste the command into your **Git Bash** terminal, use **Shift + Insert**.

![Clone the Repository](Images/Step1.png)

- Then, press Enter to start the cloning operation and wait for the success message to appear.

![Open the Library File](Images/Step2.png)

> [!IMPORTANT]
> Please keep in mind that the numbers displayed in the image might vary when you perform the same actions.  
> This is because repositories are continuously being updated and expanded. Nevertheless, the overall process remains unchanged.

> [!NOTE]
> Advantage of Cloning the Repository:  
> - **Receiving Updates:** By cloning the repository, you can easily and automatically receive new updates.  
> - **Version Control:** Using Git allows you to track changes and revert to previous versions.  
> - **Team Collaboration:** If you are working on a project with a team, you can easily sync changes from team members and collaborate more efficiently.  

## Download Zip
If you prefer not to use Git Bash or the command line, you can download the repository directly from GitHub as a ZIP file.  
Follow these steps:  
1. Navigate to the GitHub repository page and Locate the Code button:
   - On the main page of the repository, you will see a green Code button near the top right corner.

2. Download the repository:
   - Click the Code button to open a dropdown menu.
   - Select Download ZIP from the menu.

  ![Download Zip](Images/Step7.png)  

3. Save the ZIP file:
   - Choose a location on your computer to save the ZIP file and click Save.

4. Extract the ZIP file:
   - Navigate to the folder where you saved the ZIP file.
   - Right-click on the ZIP file and select Extract All... (Windows) or use your preferred extraction tool.
   - Choose a destination folder and extract the contents.

5. Access the repository:
   - Once extracted, you can access the repository files in the destination folder.

> [!IMPORTANT]
> - No Updates: Keep in mind that downloading the repository as a ZIP file does not allow you to receive updates.    
>   If the repository is updated, you will need to download it again manually.  
> - Ease of Use: This method is simpler and suitable for users who are not comfortable with Git or command-line tools.

# 📝 How to Ask Questions
If you have any questions or issues, you can raise them through the **"Issues"** section of this repository. Here's how you can do it:  

1. Navigate to the **"Issues"** tab at the top of the repository page.  

  ![Issues](Images/Step3.png)

2. Click on the **"New Issue"** button.  
   
  ![New Issue](Images/Step4.png)

3. In the **Title** field, write a short summary of your issue or question.  

4. In the "Description" field, detail your question or issue as thoroughly as possible. You can use text formatting, attach files, and assign the issue to someone if needed. You can also use text formatting (like bullet points or code snippets) for better readability.  

5. Optionally, you can add **labels**, **type**, **projects**, or **milestones** to your issue for better categorization.  

6. Click on the **"Submit new issue"** button to post your question or issue.
   
  ![Submeet New Issue](Images/Step5.png)

I will review and respond to your issue as soon as possible. Your participation helps improve the repository for everyone!  

> [!TIP]
> - Before creating a new issue, please check the **"Closed"** section to see if your question has already been answered.  
>   ![Closed section](Images/Step6.png)  
> - Write your question clearly and respectfully to ensure a faster and better response.  
> - While the examples provided above are in English, feel free to ask your questions in **Persian (فارسی)** as well.  
> - There is no difference in how they will be handled!  

> [!NOTE]
> Pages and interfaces may change over time, but the steps to create an issue generally remain the same.

# 🤝 Contributing to the Repository
To contribute to this repository, please follow these steps:
1. **Fork the Repository**  
2. **Clone the Forked Repository**  
3. **Create a New Branch**  
4. **Make Your Changes**  
5. **Commit Your Changes**  
6. **Push Your Changes to Your Forked Repository**  
7. **Submit a Pull Request (PR)**  

> [!NOTE]
> Please ensure your pull request includes a clear description of the changes you’ve made.
> Once submitted, I will review your contribution and provide feedback if necessary.

# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# 📜 License
This project is licensed under the GPL-3.0 License. This license grants you the freedom to use, modify, and distribute the project as long as you:
- Credit the original authors: Give proper attribution to the original creators.
- Disclose source code: If you distribute a modified version, you must make the source code available under the same GPL license.
- Maintain the same license: When you distribute derivative works, they must be licensed under the GPL-3.0 too.
- Feel free to use it in your projects, but make sure to comply with the terms of this license.
  
# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
