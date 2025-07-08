#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h> //for getch()
#include <time.h>  // for time_t, time(), localtime(), strftime()
 

void getPassword(char *password, int maxLen)
{
  int i = 0;
  char ch;
  while (i < maxLen - 1)
  {
    ch = getch(); // Get character without echoing to console
    if (ch == '\n' || ch == '\r')
    { // Enter key pressed
      break;
    }
    else if (ch == '\b' && i > 0)
    {                  // Backspace key pressed
      printf("\b \b"); // Remove last character from console
                       // We remove the last character by:
                       // Moving the cursor back (\b)
                       // Printing a space ( ) to erase *
                       // Moving back again (\b) to correct cursor position
                       // Also decrement i to delete from the stored string
      i--;
    }
    else
    {
      password[i++] = ch; // Add character to password
      printf("*");        // Print asterisk for each character
    }
  }
  password[i] = '\0'; // Null-terminate the string
  printf("\n");
}

struct items
{
  char item[20];
  float price;
  int quantity;
};
struct orders
{
  char customer[50];
  char date[50];
  int numofItems;
  struct items itm[50];
};
void Billbana(char name[50], char date[30])
{
  printf("\n\n\n\n\n");
  printf("==================================YASH CAFE===========================\t\t\t\t\t\t");
  printf("\n---------------------------------------------------------------------------\n");
  printf("\n Date: %s", date);
  printf("\n Invoice to %s", name);
  printf("\n");
  printf("----------------------------------------------------------------------------------------\n");
  printf("Items\t\t\t\t");
  printf("Quantity\t\t\t\t");
  printf("Total\t\t\t\t");
  printf("\n--------------------------------------------------------------------------------------------\n");
  printf("\n");
}
void kaise_Banau_Bill(char item[20], int qty, float price)
{
  printf("%s\t\t", item);
  printf(" %d\t\t", qty);
  printf("        %.2f\t\t", qty * price);
  printf("\n");
}
void Dekh_bill(float total)
{
  printf("\n");
  float dis = 0.1 * total;
  float netTotal = total - dis;
  float gst = 0.18 * netTotal;
  float grandTotal = netTotal + gst;
  printf("----------------------------------------------------------------------------------\n");
  printf("\n Subtotal\t\t\t%.2f", total);
  printf("\n Discount (10%%)\t\t\t%.2f", dis);
  printf("\n---------------------------------------------------------------------------\t\t\t\t");

  printf("\n Net Total\t\t\t%.2f", netTotal);
  printf("\n GST (18%%)\t\t\t%.2f", gst);
  printf("\n---------------------------------------------------------------------------\t\t\t\t\t\t\n");
  printf("\n Grand Total\t\t\t%.2f", grandTotal);
}
int main()
{
  int option, n, count = 2;
  char name[50];
  char saveBill = 'y', flag = 'y';
  FILE *fp;
  char password[20];
  printf("\n======================= ADMIN LOGIN ========================\n");

  while (1)
  {
    printf("\nEnter admin password to access YASH CAFE: ");
    // scanf("%s", password);
    getPassword(password, 20);
    if (strcmp(password, "YashVishnoi123") != 0)
    {
      if (count == 0)
      {
        printf("\n Access Denied!!!!! \n Exiting program.\n");
        return 0;
      }
      else
      {
        printf("Incorrect password You have %d attempts left\n", count);
        count--;
      }
    }
    else
    {
      break;
    }
  }
  printf("Login Successful! Welcome to YASH CAFE.\n");
  while (flag == 'y')
  {
    float total = 0;
    int found = 0;
    struct orders ord;
    struct orders order;

    printf("\n\n\n\n====================================YASH CAFE=======================================\t\t");
    printf("\n---------------------------------------------------------------------------------------\n");
    printf("\n 1. Generate Invoice");
    printf("\n 2. Show all Invoices");
    printf("\n 3. Search Invoices");
    printf("\n 4. Sales Report");
    printf("\n 5. Exit");

    printf("\n\n Select an option: ");
    scanf("%d", &option);

    printf("\n Your Choice is %d", option);
    printf("\n");
    switch (option)
    {
    case 1:
      printf("\n Enter Customer Name: ");
      fgetc(stdin); // Clear the newline character from the input buffer
      fgets(ord.customer, 50, stdin);
      ord.customer[strlen(ord.customer) - 1] = 0;
      strcpy(ord.date, __DATE__);
      printf("\n Enter Number of Items: ");
      scanf("%d", &n);
      ord.numofItems = n;

      for (int i = 0; i < n; i++)
      {
        fgetc(stdin);
        printf("\n\n");
        printf(" Enter Item %d Name: ", i + 1);
        fgets(ord.itm[i].item, 20, stdin);
        ord.itm[i].item[strlen(ord.itm[i].item) - 1] = '\0'; // Remove newline character
        printf(" Enter Item  Quantity:\t");
        scanf("%d", &ord.itm[i].quantity);
        printf(" Enter Item Price:\t");
        scanf("%f", &ord.itm[i].price);
        total += ord.itm[i].quantity * ord.itm[i].price;
      }
      Billbana(ord.customer, ord.date);
      for (int i = 0; i < ord.numofItems; i++)
      {
        kaise_Banau_Bill(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);
      }
      Dekh_bill(total);

      printf("\n\n Do you want to save this bill? (y/n):\t");
      scanf(" %c", &saveBill);

      if (saveBill == 'y')
      {
        fp = fopen("YashCafe.txt", "ab");

        if (fwrite(&ord, sizeof(struct orders), 1, fp))
        {
          // Export readable bill to a uniquely named text file
          char changed_name[50];
          strcpy(changed_name, ord.customer);
          for (int i = 0; changed_name[i]; i++)
          {
            if (changed_name[i] == ' ')
              changed_name[i] = '_';
          }

          // Add timestamp for uniqueness
          time_t t = time(NULL);
          struct tm *tm_info = localtime(&t);
          char timestamp[30];
          strftime(timestamp, sizeof(timestamp), "_%Y%m%d_%H%M%S", tm_info);

          char filePath[100];
          sprintf(filePath, "bills/%s%s.txt", changed_name, timestamp);
          FILE *exportFile = fopen(filePath, "w");

          if (exportFile)
          {
            fprintf(exportFile, "========================= YASH CAFE =========================\n");
            fprintf(exportFile, "Date: %s\n", ord.date);
            fprintf(exportFile, "Invoice to: %s\n", ord.customer);
            fprintf(exportFile, "------------------------------------------------------------\n");
            fprintf(exportFile, "%-20s %-10s %-10s %-10s\n", "Item", "Qty", "Price", "Total");

            float total = 0;
            for (int i = 0; i < ord.numofItems; i++)
            {
              float itemTotal = ord.itm[i].price * ord.itm[i].quantity;
              fprintf(exportFile, "%-20s %-10d %-10.2f %-10.2f\n", ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price, itemTotal);
              total += itemTotal;
            }

            float dis = 0.1 * total;
            float netTotal = total - dis;
            float gst = 0.18 * netTotal;
            float grandTotal = netTotal + gst;

            fprintf(exportFile, "------------------------------------------------------------\n");
            fprintf(exportFile, "Subtotal: %.2f\n", total);
            fprintf(exportFile, "Discount (10%%): %.2f\n", dis);
            fprintf(exportFile, "Net Total: %.2f\n", netTotal);
            fprintf(exportFile, "GST (18%%): %.2f\n", gst);
            fprintf(exportFile, "------------------------------------------------------------\n");
            fprintf(exportFile, "Grand Total: %.2f\n", grandTotal);
            fclose(exportFile);
            printf("\n Exported invoice to %s\n", filePath);
          }
          else
          {
            printf("\n Failed to export readable bill file.\n");
          }

          printf("\n Bill saved successfully.\n");
        }
        else
        {
          printf("\n Error Saving");
        }
        fclose(fp);
      }

      break;

    case 2:
      fp = fopen("YashCafe.txt", "rb");
      if (fp == NULL)
      {
        printf("\n No previous invoices found!\n");
        break;
      }
      printf("\n******************************** Previous Invoices ***********************************");

      while (fread(&order, sizeof(struct orders), 1, fp))
      {
        // printf("Enter the loop");
        float tot = 0;
        Billbana(order.customer, order.date);
        for (int i = 0; i < order.numofItems; i++)
        {
          kaise_Banau_Bill(order.itm[i].item, order.itm[i].quantity, order.itm[i].price);
          tot += order.itm[i].quantity * order.itm[i].price;
        }
        Dekh_bill(tot);
      }

      fclose(fp);
      break;

    case 3:
      printf("\n Enter the name of Customer\t");
      fgetc(stdin);
      fgets(name, 50, stdin);
      name[strlen(name) - 1] = '\0';
      fp = fopen("YashCafe.txt", "rb");
      printf("\n\n**************************** Search Result ***************************\n\n");
      while (fread(&order, sizeof(struct orders), 1, fp))
      {
        float tot = 0;
        if (!strcmp(order.customer, name))
        {

          Billbana(order.customer, order.date);
          for (int i = 0; i < order.numofItems; i++)
          {
            kaise_Banau_Bill(order.itm[i].item, order.itm[i].quantity, order.itm[i].price);
            tot += order.itm[i].quantity * order.itm[i].price;
          }
          Dekh_bill(tot);
          found = 1;
        }
      }
      if (!found)
      {
        printf("\n No records found for %s", name);
      }
      fclose(fp);

      break;

    case 4:
      fp = fopen("YashCafe.txt", "rb");
      if (fp == NULL)
      {
        printf("No sales data found!\n");
        break;
      }

      int totalCustomers = 0;
      float totalRevenue = 0;
      int itemCount[100] = {0}; // supports up to 100 unique items' quantity
      char itemNames[100][20];  // name of Unique items
      int uniqueItemCount = 0;
      struct orders tempOrder;

      while (fread(&tempOrder, sizeof(struct orders), 1, fp) == 1)
      {
        float billTotal = 0;
        totalCustomers++;

        for (int i = 0; i < tempOrder.numofItems; i++)
        {
          billTotal += tempOrder.itm[i].price * tempOrder.itm[i].quantity;

          // Check if item already counted in the list of unique items
          // If not, add it to the list
          int found = 0;
          for (int j = 0; j < uniqueItemCount; j++)
          {
            if (strcmp(itemNames[j], tempOrder.itm[i].item) == 0)
            {
              itemCount[j] += tempOrder.itm[i].quantity;
              found = 1;
              break;
            }
          }
          if (!found)
          {
            strcpy(itemNames[uniqueItemCount], tempOrder.itm[i].item);
            itemCount[uniqueItemCount] = tempOrder.itm[i].quantity;
            uniqueItemCount++;
          }
        }
        totalRevenue += billTotal;
      }

      fclose(fp);

      if (totalCustomers == 0)
      {
        printf("No customer data found.\n");
        break;
      }

      // Most sold item
      int maxIndex = 0;
      for (int i = 1; i < uniqueItemCount; i++)
      {
        if (itemCount[i] > itemCount[maxIndex])
        {
          maxIndex = i;
        }
      }

      float avgBill = totalRevenue / totalCustomers;

      printf("\n===================== SALES REPORT =====================\n");
      printf("Total Customers Served: %d\n", totalCustomers);
      printf("Total Revenue: Rs.%.2f\n", totalRevenue);
      printf("Average Bill Amount: Rs.%.2f\n", avgBill);
      printf("Most Sold Item: %s (%d units)\n", itemNames[maxIndex], itemCount[maxIndex]);
      printf("========================================================\n");
      break;

    case 5:
      printf("\n Thank you for visiting YASH CAFE!");
      exit(0);
      break;

    default:
      printf("\n Invalid option! Please try again.");
      break;
    }
    printf("\n\n Do you want to continue? (y/n): ");
    scanf(" %c", &flag);
  }

  return 0;
}