# 🐾 Animal Feed System

A simple embedded IoT game using an **ESP32**, **16x2 I2C LCD**, **Blynk IoT platform**, **servo motor**, and **buzzer**. This system simulates a virtual pet that can be fed, energized, or left alone, affecting its happiness and sadness levels. The project showcases real-time interaction between a mobile interface and hardware components.

## 🎮 Game Description

The **Animal Feed System** features a virtual pet with three interactive controls via the Blynk app:

### 1. 🟢 Start Button (V0)

* Decreases **Feed Level**.
* Decreases **Happiness** and increases **Sadness**.

### 2. 🍖 Feed Button (V1)

* Increases **Happiness** and **Feed Level**.
* Decreases **Sadness**.
* When Happiness reaches 100:

  * Activates the **servo motor** to simulate freeing the pet.
  * Displays a notification on Blynk: `Max level reached`.

### 3. ⚡ Energy Button (V2)

* Decreases **Happiness**, increases **Sadness**.
* When Sadness reaches 100:

  * Activates a **buzzer alarm**.
  * Blynk notifies: `Alarm worked`.

## 💼 Hardware Used

* **ESP32 Dev Board**
* **16x2 LCD with I2C**
* **Servo Motor (e.g., SG90)**
* **Buzzer**
* **WiFi Access Point (e.g., Wokwi-GUEST or other)**
* **Blynk IoT App (New Blynk Version)**

## 📱 Blynk Configuration

| Button Name  | Virtual Pin | Function               |
| ------------ | ----------- | ---------------------- |
| Start        | V0          | Starts feed logic      |
| Feed         | V1          | Increases happiness    |
| Energy       | V2          | Decreases happiness    |
| Alarm LED    | V3          | Shows danger condition |
| Status Label | V4          | Displays system status |

> 💡 Blynk Template ID and Auth Token are configured in the code. Replace with your own when deploying.

## 🔧 Features

* Real-time happiness/sadness level display on LCD.
* Servo activation when pet is happy (Happiness == 100).
* Buzzer alert when pet is too sad (Sadness == 100).
* Blynk dashboard shows pet status and alarm.
* Well-constrained values (0 to 100) for all variables.

## 🚀 Getting Started

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/animal-feed-system.git
   ```
2. Open the `.ino` file in Arduino IDE or PlatformIO.
3. Replace BLYNK credentials with your own.
4. Upload to an ESP32 board.
5. Set up the Blynk interface as shown above.
6. Enjoy your interactive IoT pet game!

## 📸 Screenshots
 ![alt text](screenshots/initialState.png)
![alt text](screenshots/whenEneregyBtnClicked.png)
![alt text](screenshots/whenFeedBtnClicked.png)
![alt text](screenshots/whenHappinessReachedMaximum.png)



## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

### 👨‍💻 Developed by Dilaikshan

Feel free to explore, use, and improve this simple IoT-based virtual pet game! 🐶
