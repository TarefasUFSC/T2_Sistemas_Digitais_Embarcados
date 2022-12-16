#include "sensor.hpp"

void printMenu()
{
    printf("\n|--------------------------------------|\n");
    printf("|[1] Set sensor height |\n");
    printf("|[2] Calculate user height |\n");
    printf("|[0] Stop code |\n");
    printf("|--------------------------------------|\n");
}

void printAuxMenu()
{
    printf("\n|--------------------------------------|\n");
    printf("|[1] Calculate actual sensor height |\n");
    printf("|[2] Set custom sensor height |\n");
    printf("|[3] Set default sensor height(300) |\n");
    printf("|--------------------------------------|\n");
}

extern "C" void app_main();

void app_main()
{
    serial.begin(9600);
    Sensor sensor(PIN16, PIN5, 300);
    while (1)
    {
        // Print default menu
        printMenu();

        char choiceBuffer[1];
        serial.readString((uint8_t *)choiceBuffer, 1);
        int choice = atoi(choiceBuffer);
        if (choice == 1)
        {
            printAuxMenu();
            char secondChoiceBuffer[1];
            serial.readString((uint8_t *)secondChoiceBuffer, 1);
            int secondChoice = atoi(secondChoiceBuffer);

            if (secondChoice == 1)
            {
                int newHeight = sensor.calculateHeight(1);
                printf("\n Current height of sensor: %i", newHeight);
                sensor.baseSensorHeight = newHeight;
            }
            else if (secondChoice == 2)
            {
                printf("\n Enter custom sensor height: ");
                char customHeightBuffer[4];
                serial.readString((uint8_t *)customHeightBuffer, 4);
                int customHeight = atoi(customHeightBuffer);
                sensor.baseSensorHeight = customHeight;
            }
            else if (secondChoice == 3)
            {
                sensor.baseSensorHeight = 300;
            }
        }
        else if (choice == 2)
        {
            int userHeight = sensor.calculateHeight(0);
            printf("\n User height: %i", userHeight);
        }
        else if (choice == 0)
        {
            break;
        }
    }
}