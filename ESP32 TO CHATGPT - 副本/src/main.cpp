#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "wife 名字";
const char* password = "wife 密码";
const char* API_ENDPOINT = "url";//因为国内网络原因需要部署函数详情可看 
//教程：https://github.com/Ice-Hazymoon/openai-scf-proxy     2. https://github.com/easychen/openai-api-proxy获取url
const char* API_KEY = "密钥";

HTTPClient http;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  int wifiConnectResult = WiFi.waitForConnectResult();
  if (wifiConnectResult != WL_CONNECTED) {
    Serial.print("WiFi connection failed. Error code: ");
    Serial.println(wifiConnectResult);
    return;
  }

  Serial.print("WiFi connected with IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available()) {  // Check if there is user input from serial
    String userInput = Serial.readStringUntil('\n');  // Read user input until newline character
    userInput.trim();  // Remove whitespace at the beginning and end of user input
//检查串口输入，通过串口输入问题
    if (userInput.length() > 0) {  // If user input is not empty
      http.begin(API_ENDPOINT);
      http.setTimeout(180000);// Set HTTP request timeout to 10 seconds
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Authorization", "Bearer " + String(API_KEY));
      String requestBody = "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"" + userInput + "\"}],\"stream\": false}";
      int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    
      String responseBody = http.getString();

      // Parse the JSON response
      DynamicJsonDocument responseJson(2048);
      deserializeJson(responseJson, responseBody);

      Serial.println("Response: " + responseBody);

      // Access the response data
      String message = responseJson["choices"][0]["message"]["content"];

      Serial.print("User: ");
      Serial.println(userInput);
      Serial.print("ChatGPT: ");
      Serial.println(message);
    
  } else {
    Serial.print("Error sending request. Response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
}

delay(100); }