#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Initializes `customers` array of size `max_cust` to an appropriate default value
// Also intiailizes the first `n` entries of the `kiosks` array to an appropriate default value
void initArrays(int customers[], int max_cust, int kiosks[], int n);

// Finds and returns the size of the largest contiguous range of free kiosks
// Also prints out the first and last free kiosk index of the largest free range
// kiosks = array of kiosks
// n = size of used elements in the kiosks array
// return the number of kiosks in the largest contiguous free range
int getAndPrintMaxFreeRange(int kiosks[], int n);
// Returns true if `choice` is between 0 and `n`-1, inclusive,
// false otherwise.
bool isValidChoice(int choice, int n);

// Checks if the `choice`-th kiosk is free and then 
// updates the `choice`-th kiosk to contain customer with ID = `cust_id`.
// Also sets the starting time of the `cust_id`-th customer to `tick`.
// Does nothing if the `choice`-th kiosk is already in use.
void addCustomer(int customers[], int cust_id, int kiosks[], int choice, int tick);

// Checks if the `choice`-th kiosk is being used by a customer and then 
// sets the `choice`-th kiosk back to free/unoccupied.
// Also computes the elapsed time the customer was at that kiosk and sets
// the customer ID's entry in the customer array with that elapsed time.
// Does nothing if the `choice`-th kiosk was already free.
void removeCustomer(int customers[], int kiosks[], int choice, int tick);

// Scans the `num_cust` elements of the customers array to find and return
// the maximum time a customer used a kiosk
int maxTimeCustomer(int customers[], int num_cust);

// Scans through all the `n` kiosks and *ends* their usage as of the current
// time `tick` updating their usage time in the customers array (of size `num_cust`).  
void calculateTimesOfRemainingCustomers(int customers[], int kiosks[], int n, int tick);

int main()
{
    // You may add more variable declarations if desired
    int n, tick = 1, num_cust = 0;
    int kiosks[50];
    int customers[100];
    cin >> n;

    // Initialize arrays to appropriate default values
    initArrays(customers, 100, kiosks, n);

    // stores the sum of the larges free range just before a new customer is added 
    int avgMaxFreeRange = 0;  
    bool quit = false;
    while(num_cust <= 100 && !quit )
    {  
        // Update the largest contiguous free range of kiosks if it has changed
        
        cout<<"status "<<tick << " "<< num_cust<< " "<<avgMaxFreeRange<<endl;
        char option;
        int choice;
        cout << "Enter event: 'a location', 'r location', or 't': " << endl;
        cin >> option;
  
        // Complete the rest of the body of this loop to get any additional
        // input and perform the appropriate processing based on the input
        // option. Each of the functions prototyped above must be called somewhere
        // in main() -- some are already called in the provided code.
        
          
        if (option == 'a') {
    
            int maxFreeRange = getAndPrintMaxFreeRange(kiosks, n);
            avgMaxFreeRange += maxFreeRange;
        //if option is character a which means the kiosk remains empty then we take in an additional number
            cout<<"Enter the choice of kiosk you like"<<endl;
            cin>>choice;
            if (isValidChoice(choice,n)){
        //if option is valid then we continue 
                addCustomer(customers, num_cust, kiosks, choice, tick);
                num_cust++;
            }
        }
            
        }
        else if (option == 't'){
            tick++;
            
        }
        else if (option == 'r'){
        
          cin>>choice; 
          removeCustomer(customers, kiosks, choice, tick);
           
          }
        else if (option == 'q'){
            quit = true;
        
    }
   
    // Do not change this code. It is necessary to meet the desired test format
    if(num_cust != 0){
        
        calculateTimesOfRemainingCustomers(customers, kiosks, n, tick);
        cout << "Max time: " << maxTimeCustomer(customers, num_cust) << endl;
        cout << setprecision(2) << fixed;
        cout << "Average Max Free Range: " <<  avgMaxFreeRange / (double) num_cust << endl;
    }
    
    return 0;
    
}

// Complete...Do not change
bool isValidChoice(int choice, int n)
{
    
    return choice >= 0 && choice < n;
}

// Complete...Do not change
void addCustomer(int customers[], int cust_id, int kiosks[], int choice, int tick)
{
    if(kiosks[choice] == -1){
        customers[cust_id] = -tick;
        kiosks[choice] = cust_id;
    }
}

// Complete...Do not change
void removeCustomer(int customers[], int kiosks[], int choice, int tick)
{
    if(kiosks[choice] != -1)
    {
        int cust_id = kiosks[choice];
        customers[cust_id] = tick - (-customers[cust_id]);
        kiosks[choice] = -1;
    }
}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
void initArrays(int customers[], int max_cust, int kiosks[], int n)
{
    
    for (int d = 0; d < max_cust; d++){
        customers[d] = 0;
    }
    
    for (int j = 0; j < n; j++){
        kiosks[j] = -1;
    }

}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
int getAndPrintMaxFreeRange(int kiosks[], int n)
{
    int calculated_amount=0;
    int consecutiverange = 0;
    int first = 0;
    int last = 0;
    
    for (int i = 0; i < n; i++){
        if (kiosks[i] == -1){
            consecutiverange++;
        }
        else{
            if (consecutiverange > calculated_amount){
                calculated_amount = consecutiverange;
                first = i + 1 - consecutiverange;
                last = i;
            }
            
            consecutiverange = 0;
        }
        
    }
    if (consecutiverange > calculated_amount){
        calculated_amount = consecutiverange;
        first = n - consecutiverange;
        last = n-1;
    }


    // Before returning perform a `cout` that prints a message like:
    //    Max free range is between kiosk 0 and 19
    // where 0 and 19 are replaced with the start and end of the largest free
    // contiguous kiosk range
    // return the size of the largest free range  
    cout<<"Max free range is between kiosk "<< first << " and " << last <<endl;
    return calculated_amount;
    

}


// You complete. (See description above prototype.)
// Do not change the prototype / signature.
void calculateTimesOfRemainingCustomers(int customers[], int kiosks[], int n, int tick) 
{
    for (int i = 0; customers[i] != 0; i++){
        if(customers[i] < 0){
            customers[i] = tick-(-customers[i]);
        }
    }

}

// You complete. (See description above prototype.)
// Do not change the prototype / signature.
int maxTimeCustomer(int customers[], int num_cust)
{
    int maxtick = 0;
   
    
    for(int index = 0; index < num_cust; index++){
        if (abs(customers[index]) > maxtick){
            maxtick = abs(customers[index]);
            
        }
    }
  
    return maxtick;
    
}



