#include<bits/stdc++.h>
using namespace std;
const int MIN_TRAIN_NO = 10000;
const int MAX_TRAIN_NO = 99999;
const set<string> validTrainClasses = {"SL","2S","3A","1A","2A","CC","GN"};
const set<string> validWeekDays = {"M","T","W","TH","F","SAT","S"};

string normalizeText(string s) {

    string result;
    bool spaceFound = false;

    // remove extra spaces (multiple → single)
    for(char ch : s) {
        if(isspace(ch)) {
            if(!spaceFound) {
                result += ' ';
                spaceFound = true;
            }
        } else {
            result += ch;
            spaceFound = false;
        }
    }

    // trim leading & trailing space
    if(!result.empty() && result.front() == ' ')
        result.erase(result.begin());
    if(!result.empty() && result.back() == ' ')
        result.pop_back();

    // capitalize properly (Title Case)
    bool newWord = true;
    for(char &ch : result) {
        if(ch == ' ') {
            newWord = true;
        } else {
            ch = newWord ? toupper(ch) : tolower(ch);
            newWord = false;
        }
    }

    return result;

}

class Passenger {

    public:

    string Name;
    int Age;
    char Gender;

};

class Ticket {

    private:

    long long PNR;
    double Fare;
    int TotalPassengers;
    int TrainNumber;
    string TrainName;
    string Source, Destination;
    string TrainClass;
    vector<Passenger> Passengers;
    string DateOfJourney;

    public:

    // SETTERS
    void setPNR(long long p){ PNR = p; }
    void setTrainNumber(int n){ TrainNumber = n; }
    void setTrainName(string n){ TrainName = n; }
    void setRoute(string s, string d){ Source=s; Destination=d; }
    void setClass(string c){ TrainClass = c; }
    void setFare(double f){ Fare = f; }
    void setPassengers(vector<Passenger> p){ Passengers = p; }
    void setTotalPassengers(int p) { TotalPassengers = p; }
    void setDateOfJourney(string doj) { DateOfJourney = doj; };


    // GETTERS
    long long getPNR(){ return PNR; }
    int getTrainNumber(){ return TrainNumber; }
    string getTrainName() { return TrainName; }
    string getClass(){ return TrainClass; }
    double getFare(){ return Fare; }
    vector<Passenger> getPassengers(){ return Passengers; }
    string getSource() { return Source; }
    string getDestination() { return Destination; }
    int getTotalPassengers() { return TotalPassengers; }
    string getDateOfJourney() { return DateOfJourney; }

};


class Train{

    private:

    int TrainNumber,TotalSeats,BookedSeats;
    string TrainName,Source,Destination;
    vector<string> RunningDays;
    map<string,int> SeatsAvailablePerClass;
    map<string,pair<int,pair<int,int>>> Stoppages; // station,kms,stop_no,price

    public:

    // GETTERS
    int getTrainNumber() { return TrainNumber; }
    string getTrainName() { return TrainName; }
    string getSource() { return Source; }
    string getDestination() { return Destination; }
    vector<string> getRunningDays() { return RunningDays; }
    map<string,int> &getSeatsAvailablePerClass() { return SeatsAvailablePerClass; }
    map<string,pair<int,pair<int,int>>> &getStoppages() { return Stoppages; }
    int getTotalSeats() { return TotalSeats; }
    int getBookedSeats() { return BookedSeats; }


    // SETTERS
    void setTrainNumber(int number) { TrainNumber = number; }
    void setTrainName(string name) { TrainName = name; }
    void setSource(string src) { Source = src; }
    void setDestination(string dst) { Destination = dst; }
    void setRunningDays(vector<string> Days) { RunningDays = Days; }
    void setSeatsAvailablePerClass(string trainclass, int seats) { SeatsAvailablePerClass[trainclass] = seats; }
    void setStoppages(string stationname, int kms, int stoppage_no, int ticketprice) { Stoppages[stationname] = {kms,{stoppage_no,ticketprice}}; }
    void setTotalSeats(int seats) { TotalSeats = seats; }
    void setBookedSeats(int seats) { BookedSeats = seats; }

};


class Files{

    public:

    void TruncateFile(const string &filePath) {
        ofstream fout(filePath, ios::out | ios::trunc);
        fout.close();
    }   

    void SaveTrainsInfoToFile(vector<Train> &TrainList) {
    
        string src, dst, TrainName;
        ofstream fout("D:\\Desktop\\trains.txt", ios::app);
        
        for (auto &t : TrainList) {
            // replace spaces with underscores for safe single-token saving
            TrainName = t.getTrainName();
            src  = t.getSource();
            dst  = t.getDestination();
            replace(TrainName.begin(), TrainName.end(), ' ', '_');
            replace(src.begin(),  src.end(),  ' ', '_');
            replace(dst.begin(),  dst.end(),  ' ', '_');

            fout << t.getTrainNumber() << " "
                << TrainName << " "
                << src  << " "
                << dst  << " "
                << t.getTotalSeats() << " "
                << t.getBookedSeats() << " ";

            map<string,int> trainclasses = t.getSeatsAvailablePerClass();
            fout << trainclasses.size() << " ";

            for(auto &x : trainclasses){
                fout << x.first << " " << x.second << " ";
            }
            
            vector<string> Days = t.getRunningDays();
            fout << Days.size() << " ";

            for(auto &x : Days){
                fout << x << " ";
            }

            map<string,pair<int,pair<int,int>>> stoppages = t.getStoppages();
            fout << stoppages.size() << " ";

            for(auto &x : stoppages){
                string station = x.first;
                replace(station.begin(), station.end(), ' ', '_');
                fout << station << " " << x.second.first << " "
                << x.second.second.first << " "
                << x.second.second.second << " ";
            }

            fout << endl;

        }
        
        TrainList.clear();
        fout.close();
    
    }

    vector<Train> LoadTrainsInfoFromFile(){

        int TotalSeats, BookedSeats, TrainNumber;
        string TrainName, src, dst;
        vector<Train> TrainList;
        
        ifstream fin("D:\\Desktop\\trains.txt");


        while (fin >> TrainNumber >> TrainName >> src >> dst >> TotalSeats >> BookedSeats) {

            replace(TrainName.begin(), TrainName.end(), '_', ' ');
            replace(src.begin(),  src.end(),  '_', ' ');
            replace(dst.begin(),  dst.end(),  '_', ' ');

            Train train;
            train.setTrainNumber(TrainNumber);
            train.setTrainName(TrainName);
            train.setSource(src);
            train.setDestination(dst);
            train.setTotalSeats(TotalSeats);
            train.setBookedSeats(BookedSeats);


            /* ---------- LOAD CLASSES ---------- */
            int TrainClassCount;
            fin >> TrainClassCount;

            for (int i = 0; i < TrainClassCount; i++) {

                string TrainClassName;
                int Seats;

                fin >> TrainClassName >> Seats;
                train.setSeatsAvailablePerClass(TrainClassName, Seats);
            }


            /* ---------- LOAD RUNNING DAYS ---------- */
            int DaysCount;
            fin >> DaysCount;
            vector<string> UniqueDays;

            for (int i = 0; i < DaysCount; i++) {
                string day;
                fin >> day;
                UniqueDays.push_back(day);
            }

            train.setRunningDays(UniqueDays);


            /* ---------- LOAD STOPPAGES ---------- */
            int StopCount;
            fin >> StopCount;

            for (int i = 0; i < StopCount; i++) {

                string StationName;
                int Stoppage_No, Kms, TicketPrice;

                fin >> StationName >> Kms >> Stoppage_No >> TicketPrice;

                replace(StationName.begin(),StationName.end(),'_',' ');

                train.setStoppages(StationName, Kms, Stoppage_No, TicketPrice);

            }

            TrainList.push_back(train);

        }

        fin.close();
        return TrainList;

    }

    unordered_map<string,string> LoadUsersFromFile() {
    
        unordered_map<string,string> UsersCredentials;
        ifstream fin("D:\\Desktop\\UsersCredentials.txt");

        string UserName, Password;

        while (fin >> UserName >> Password) {
            UsersCredentials[UserName] = Password;
        }

        fin.close();
        return UsersCredentials;

    }

    void SaveUsersToFile(unordered_map<string,string> &UsersCredentials) {
    
        ofstream fout("D:\\Desktop\\UsersCredentials.txt", ios::app);

        for (auto &p : UsersCredentials) {
            fout << p.first << " " << p.second << endl;
        }

        UsersCredentials.clear();
        fout.close();

    }

    void SaveTicketsToFile(unordered_map<long long,Ticket> &BookedTickets){

        string TrainName, src, dst;
        ofstream fout("D:\\Desktop\\BookedTickets.txt", ios::app);

        for(auto &bt : BookedTickets){

            Ticket &ticket = bt.second;

            TrainName = ticket.getTrainName();
            src = ticket.getSource();
            dst = ticket.getDestination();

            replace(TrainName.begin(), TrainName.end(), ' ', '_');
            replace(src.begin(), src.end(), ' ', '_');
            replace(dst.begin(), dst.end(), ' ', '_');

            fout << ticket.getPNR() << " " << ticket.getTrainNumber() << " " << TrainName << " "
                 << ticket.getDateOfJourney() << " " << src << " " << dst << " " << ticket.getClass() << " "
                 << ticket.getFare() << " " << ticket.getTotalPassengers() << " ";


            for(auto &p : ticket.getPassengers()){
                string name = p.Name;
                replace(name.begin(), name.end(), ' ', '_');
                fout << name << " " << p.Age << " " << p.Gender << " ";
            }
            
            fout << endl;

        }

        BookedTickets.clear();
        fout.close();

    }


    unordered_map<long long, Ticket> LoadTicketsFromFile() {

        unordered_map<long long, Ticket> BookedTickets;
        ifstream fin("D:\\Desktop\\BookedTickets.txt");

        long long PNR;
        double Fare;
        int TrainNumber;
        string TrainName, src, dst, TrainClass, DateOfJourney;

        while(fin >> PNR >> TrainNumber >> TrainName >> DateOfJourney >> src >> dst >> TrainClass >> Fare){

            replace(TrainName.begin(), TrainName.end(), '_', ' ');
            replace(src.begin(), src.end(), '_', ' ');
            replace(dst.begin(), dst.end(), '_', ' ');

            Ticket ticket;
            ticket.setPNR(PNR);
            ticket.setTrainNumber(TrainNumber);
            ticket.setTrainName(TrainName);
            ticket.setDateOfJourney(DateOfJourney);
            ticket.setRoute(src, dst);
            ticket.setClass(TrainClass);
            ticket.setFare(Fare);

            int PassengerCount;
            fin >> PassengerCount;
            vector<Passenger> Passengers;

            for(int i=0; i<PassengerCount; i++){

                Passenger p;
                fin >> p.Name >> p.Age >> p.Gender;

                replace(p.Name.begin(), p.Name.end(), '_', ' ');
                Passengers.push_back(p);
            }

            ticket.setPassengers(Passengers);
            ticket.setTotalPassengers(Passengers.size());
            BookedTickets[PNR] = ticket;
        }

        fin.close();
        return BookedTickets;

    }

    vector<pair<int,double>> LoadCancelledTicketsChargesFromFile(){

        vector<pair<int,double>> CancelledTicketsCharges;
        ifstream fin("D:\\Desktop\\CancelledTicketsCharges.txt");

        int TrainNumber;
        double TicketCost;

        while (fin >> TrainNumber >> TicketCost) {
            CancelledTicketsCharges.push_back({TrainNumber,TicketCost});
        }

        fin.close();
        return CancelledTicketsCharges;

    }

    void SaveCancelledTicketsChargesToFile(vector<pair<int,double>> &CancelledTicketsCharges) {
    
        ofstream fout("D:\\Desktop\\CancelledTicketsCharges.txt", ios::app);

        for (auto &p : CancelledTicketsCharges) {
            fout << p.first << " " << p.second << endl;
        }

        CancelledTicketsCharges.clear();
        fout.close();

    }

};

class InputValidator{

    public:

    bool isValid(const string &name) {

        if(name.empty()) return false;

        for(char ch : name) {
            if(!(isalpha(ch) || ch == ' ')) {
                return false;
            }
        }
        return true;
    }

    int getValidTrainNumber() {

        int TrainNumber;

        while(true){

            cout << "\nEnter Train Number (5 digits): ";
            cin >> TrainNumber;

            if(cin.fail() || TrainNumber < MIN_TRAIN_NO || TrainNumber > MAX_TRAIN_NO) {
                cout << "\n[ERROR] Invalid Train Number format.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            return TrainNumber;
        }

    }

    string getValidTrainName(){

        string TrainName;

        while(true){

            cout << "\nEnter Train Name: ";
            getline(cin, TrainName);

            TrainName = normalizeText(TrainName);

            if(TrainName.empty()){
                cout << "\n[ERROR] Input cannot be empty or spaces only.\n";
                continue;
            }

            if(!isValid(TrainName)){
                cout << "\n[ERROR] Invalid Train Name.";
                cout << "\nAllowed characters: Alphabets, spaces.";
                cout << "\nExample: Rajdhani Express, Shatabdi Express\n";
                continue;
            }
            
            return TrainName;
        }
    }

    string getValidStation(string st){

        string StationName;

        while(true){

            cout << "\nEnter "<<st<<" Station: ";
            getline(cin, StationName);

            StationName = normalizeText(StationName);

            if(StationName.empty()){
                cout << "\n[ERROR] Input cannot be empty or spaces only.\n";
                continue;
            }

            if(!isValid(StationName)){
                cout << "\n[ERROR] Invalid Station Name.";
                cout << "\nAllowed characters: Alphabets, spaces.";
                cout << "\nExample: Amritsar Jn, Katihar Jn\n";
                continue;
            }

            return StationName; 
        }
    }

};

class TrainService {
    
    public:

    pair<bool,vector<Train>::iterator> isTrainExist(int trainNumber,vector<Train> &TrainList){

        auto it = find_if(TrainList.begin(), TrainList.end(),[&](Train &tr){
            return tr.getTrainNumber() == trainNumber;
        });

        if(it != TrainList.end()) return {true,it};
        return {false,TrainList.end()};

    }

};

class Admin{

    private:

    Files f;
    TrainService services;
    InputValidator validator;

    bool hasBookedTickets(int trainNo){

        auto tickets = f.LoadTicketsFromFile();

        for(auto &x : tickets){
            if(x.second.getTrainNumber() == trainNo)
                return true;
        }
        return false;

    }

    
    void getValidRunningDays(vector<string> &UniqueDays){

        int count;
        string day;

        while (true) {

            cout << "\nEnter Number of Running Days (1-7): ";
            cin >> count;

            if (cin.fail() || count < 1 || count > 7) {
                cout << "\n[ERROR] Invalid running days count.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            break;
        }

        cout << "\nEnter Running Days (S M T W TH F SAT):\n";

        while(count){

            cout << "\nEnter Day " << (UniqueDays.size() + 1) << " of " << (UniqueDays.size() + count) << ": ";
            cin>>day;
            transform(day.begin(),day.end(),day.begin(),::toupper);

            if(day.empty()){
                cout << "\n[ERROR] Input cannot be empty or spaces only.\n";
                continue;
            }

            if(!validWeekDays.count(day)) {
                cout << "\n[ERROR] Invalid day. Allowed values: S M T W TH F SAT\n";
                continue;
            }

            auto it = find(UniqueDays.begin(),UniqueDays.end(),day);
            if(it != UniqueDays.end()){
                cout << "\n[ERROR] "<<day<<" already added.\n";
                continue;
            }

            UniqueDays.push_back(day);
            count--;
        }
    }

    void getValidTrainClasses(Train &train, int &TotalSeats){

        int count, seats;
        string TrainClass;

        while (true) {

            cout << "\nEnter Number of Available Travel Classes: ";
            cin >> count;

            if (cin.fail() || count <= 0) {
                cout << "\n[ERROR] At least one travel class is required.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            break;
        }

        while(count){

            cout << "\nEnter Train Class Code (e.g. SL, 3A, 2A): ";
            cin>>TrainClass;

            TrainClass = normalizeText(TrainClass);
            transform(TrainClass.begin(), TrainClass.end(), TrainClass.begin(), ::toupper);

            if(TrainClass.empty()){
                cout << "\n[ERROR] Input cannot be empty or spaces only.\n";
                continue;
            }

            if(!validTrainClasses.count(TrainClass)){
                cout << "\n[ERROR] Invalid class code.\n";
                continue;
            }

            if (train.getSeatsAvailablePerClass().count(TrainClass)) {
                cout << "\n[ERROR] Class already added.\n";
                continue;
            }

            while(true){

                cout << "\nEnter Seat Capacity for "<<TrainClass<<": ";
                cin>>seats;

                if(cin.fail() || seats <= 0){
                    cout << "\n[ERROR] Seat capacity must be greater than zero.\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }
                break;
            }

            TotalSeats += seats;
            train.setSeatsAvailablePerClass(TrainClass,seats);
            count--;
            cout<<"\n\n";
        }
    }

    void getIntermediateStationsInput(Train &train, int &Stop_No){

        string StationName;
        int Kms, TicketPrice;
        string Source = train.getSource();

        while(true){

            cout<<"\nEnter Station Name: ";
            getline(cin,StationName);
            StationName = normalizeText(StationName);

            if(StationName.empty()){
                cout << "\n[ERROR] Input cannot be empty or spaces only.\n";
                continue;
            }

            if(!validator.isValid(StationName)){
                cout << "\n[ERROR] Invalid input. Please try again.\n";
                continue;
            }
            break;
        }

        while(true){

            cout<<"\nTotal Distance From "<< Source<<" to "<<StationName<<": ";
            cin>>Kms;

            if(cin.fail() || Kms <= 0){
                cout << "\n[ERROR] Distance must be a greater than zero.\n";
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                continue;
            }
            break;
        }

        while(true){

            cout << "\nTotal Price to reach "<< StationName << " from "<< Source <<": ";
            cin>>TicketPrice;

            if(cin.fail() || TicketPrice <= 0){
                cout << "\n[ERROR] Ticket price must be greater than zero.\n";
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                continue;
            }
            break;
        }

        if(train.getStoppages().count(StationName)){
            cout << "\n[ERROR] Station already added as stoppage.\n";
            return;
        }

        train.setStoppages(StationName,Kms,Stop_No,TicketPrice);
        Stop_No++;

    }

    void getValidStoppages(Train &train){

        int choice, Stop_No = 2;
        train.setStoppages(train.getSource(),0,1,0);

        do{

            cout << "\n1. Add Intermediate Station (exclude Source but must include Destination)";
            cout << "\n2. Finalize Train Route\n";

            cout<<"\nEnter your choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 2) {
                cout << "\n[ERROR] Invalid menu option.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }

            switch(choice){

                case 1: {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getIntermediateStationsInput(train,Stop_No);
                    break;
                }
                case 2: break;
            }

        }while(choice != 2);


    }

    void ReturnToAdminDashboard(){

        cout << "\n[INFO] Returning to Admin Dashboard...\n";
        cout << "Please wait...\n";
        cin.ignore();
        cout << "\nPress ENTER to continue...";
        cin.get();

    }


    public:

    void AdminDashboard(){

        int choice;
        
        do{

            cout << "\n\n******************************************************* ADMIN DASHBOARD *******************************************************\n";
            cout << "\n1. Add New Train\n2. Delete Train\n3. Update Train Information\n4. View All Trains\n5. View Train Details\n6. Total Earning\n7. Logout\n";

            while(true){

                cout<<"\nEnter your choice: ";
                cin>>choice;

                if(cin.fail() || choice > 7 || choice < 1){
                    cout << "\n[ERROR] Invalid menu option.\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }

                break;

            }

            switch(choice){

                case 1: AddNewTrain(); break;
                case 2: DeleteTrain(); break;
                case 3: UpdateTrainInfo(); break;
                case 4: ViewAllTrain(); break;
                case 5: ViewTrainDetails(); break;
                case 6: TotalEarning(); break;
                case 7: break;
            }

        }while(choice != 7);


        cout << "\n===============================================================================================================================\n";
        cout << "                                       Thank you for using Indian Railways Admin Portal.                                         \n";
        cout << "\n===============================================================================================================================\n";

    }

    void AddNewTrain(){

        Train train;
        int TotalSeats = 0;
        int Stop_No = 1;
        vector<Train> TrainList = f.LoadTrainsInfoFromFile();
    
        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                 INDIAN RAILWAYS - ADMIN PORTAL                                                    \n";
        cout << "                                                     ADD NEW TRAIN SERVICE                                                         \n";
        cout << "===============================================================================================================================\n";
        
        

        /* ---------- TRAIN NUMBER ---------- */
        int TrainNumber = validator.getValidTrainNumber();
        train.setTrainNumber(TrainNumber);


        /* ---------- CHECK WHETHER TRAIN NUMBER EXISTS OR NOT ---------- */
        bool exist = services.isTrainExist(TrainNumber,TrainList).first;
        TrainList.clear(); /* ----- CLEARING THE TRAINLIST VECTOR -------*/

        if(exist){
            cout << "\n[WARNING] Train Number already exists in the system.\n";
            cout << "Please use a unique Train Number and Try Again.\n";
            ReturnToAdminDashboard();
            return;
        }
        

        /* ---------- TRAIN NAME ---------- */
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string TrainName = validator.getValidTrainName();
        train.setTrainName(TrainName);

        
        /* ---------- SOURCE & DESTINATION ---------- */
        string Source, Destination;

        while(true){
            Source = validator.getValidStation("Source");
            Destination = validator.getValidStation("Destination");

            if(Source != Destination) break;

            cout << "\n[ERROR] Source and Destination cannot be same.\n";
        }
        train.setSource(Source);
        train.setDestination(Destination);


        /* ---------- RUNNING DAYS ---------- */
        vector<string> UniqueDays;

        cout << "\n---------------------------------------------- TRAIN RUNNING DAYS CONFIGURATION -----------------------------------------------\n";
        getValidRunningDays(UniqueDays);
        train.setRunningDays(UniqueDays);


        /* ---------- TRAIN CLASSES ---------- */
        cout << "\n------------------------------------------------- COACH & SEAT CONFIGURATION --------------------------------------------------\n";
        getValidTrainClasses(train,TotalSeats);
        train.setTotalSeats(TotalSeats);
        train.setBookedSeats(0);

        
        /* ---------- STATION STOPPAGE CONFIGURATION ---------- */
        cout << "\n------------------------------------------------ STATION STOPPAGE CONFIGURATION -----------------------------------------------\n";
        getValidStoppages(train);

        
        /* ---------- TRAIN SUMMARY ---------- */
        cout << "\n==================================================== TRAIN SERVICE SUMMARY ====================================================\n";
        cout << "Train Number       : " << TrainNumber << endl;
        cout << "Train Name         : " << TrainName << endl;
        cout << "Route              : " << Source << " -> " << Destination << endl;
        cout << "Running Days       : ";
        if(UniqueDays.size() == 7) cout << "Daily";
        else{
            for(auto &d : UniqueDays) cout << d << " ";
        }
        cout << "\nTotal Capacity     : " << TotalSeats << endl;
        cout << "===============================================================================================================================\n\n";
        


        /* ---------- CONFIRMATION ---------- */
        string confirm;

        while (true) {

            cout << "\nConfirm creation of this train service? (Y/N): ";
            cin >> confirm;

            if (confirm == "Y" || confirm == "y") break;
            if (confirm == "N" || confirm == "n") {
                cout << "\n[INFO] Train creation cancelled by Admin.\n";
                ReturnToAdminDashboard();
                return;
            }
            cout << "\n[ERROR] Please enter Y or N only.\n";
        }

        /* ---------- FINAL SAVE ---------- */
        TrainList.push_back(train);
        f.SaveTrainsInfoToFile(TrainList);
      
        cout << "\n[SUCCESS] Train service has been successfully added to the system.\n";
        cout << "[INFO] Service is now available for passenger booking.\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        
        ReturnToAdminDashboard();
        
    }


    void DeleteTrain(){

        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        if(TrainList.empty()){
            cout << "\n[INFO] No train services are currently available in the system.\n";
            ReturnToAdminDashboard();
            return;
        }

        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                  INDIAN RAILWAYS - ADMIN PORTAL                                                   \n";
        cout << "                                                       DELETE TRAIN SERVICE                                                        \n";
        cout << "===============================================================================================================================\n";
        


        /* ---------- TRAIN NUMBER ---------- */
        int TrainNumber = validator.getValidTrainNumber();


        /* ---------- CHECK WHETHER TRAIN EXISTS OR NOT---------- */
        auto result = services.isTrainExist(TrainNumber,TrainList);
        bool exist = result.first;
        Train &train = *(result.second);

        if(!exist){
            cout << "\n[WARNING] Train number not found in the system.\n";
            TrainList.clear();
            ReturnToAdminDashboard();
            return;
        }

        /* ---------- TRAIN PREVIEW ---------- */
        cout << "\n==================================================== TRAIN SERVICE DETAILS ====================================================\n";
        cout << "Train Number : " << train.getTrainNumber() << endl;
        cout << "Train Name   : " << train.getTrainName() << endl;
        cout << "Route        : " << train.getSource()<< " -> " << train.getDestination();
        cout << "\n===============================================================================================================================\n";
        

        /* ---------- CONFIRMATION ---------- */
        cout << "\n[WARNING] This action will permanently delete the train service.";

        string confirm;

        while (true) {

            cout << "\nDo you want to proceed? (Y/N): ";
            cin >> confirm;

            if (confirm == "Y" || confirm == "y") break;
            if (confirm == "N" || confirm == "n") {
                cout << "\n[INFO] Train deletion cancelled by Admin.\n";
                TrainList.clear();
                ReturnToAdminDashboard();
                return;
            }

            cout << "\n[ERROR] Please enter Y or N only.\n";
        }


        /* ---------- DELETE OPERATION ---------- */
        TrainList.erase(result.second);


        /* --------- FINAL SAVE --------- */
        f.TruncateFile("D:\\Desktop\\trains.txt");
        f.SaveTrainsInfoToFile(TrainList);


        cout << "\n===============================================================================================================================";
        cout << "\n[SUCCESS] Train service has been successfully removed from the system.\n";
        cout << "[INFO] Changes have been saved permanently.\n";
        ReturnToAdminDashboard();

    }


    void UpdateTrainInfo(){


        cout << "\n===============================================================================================================================\n";
        cout << "                                                 INDIAN RAILWAYS - ADMIN PORTAL                                                  \n";
        cout << "                                                  UPDATE TRAIN DETAILS SERVICE                                                   ";
        cout << "\n===============================================================================================================================\n";


        vector<Train> TrainList = f.LoadTrainsInfoFromFile();
        int TrainNumber;

        while(true){

            cout << "\nEnter Train Number to Update (5 digits): ";
            cin >> TrainNumber;

            if(cin.fail() || TrainNumber > MAX_TRAIN_NO || TrainNumber < MIN_TRAIN_NO){
                cout << "\n[ERROR] Invalid Train Number format.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }

            break;

        }

        auto result = services.isTrainExist(TrainNumber,TrainList);
        bool exist = result.first;

        if(!exist){
            cout << "\n[ERROR] No train service found for the given Train Number.\n";
            TrainList.clear();
            ReturnToAdminDashboard();
            return;
        }

        Train &train = *(result.second);
        bool booked = hasBookedTickets(TrainNumber);

        if(booked){
            cout << "\n[WARNING] Tickets have already been booked for this train.\n";
            cout << "[INFO] Train configuration update is restricted to maintain data integrity.\n";
            TrainList.clear();
            ReturnToAdminDashboard();
            return;
        }

        cout << "\n[IMPORTANT NOTICE]\n";
        cout << "   * Updating train details will RESET existing data for selected fields.\n";
        cout << "   * You will be required to re-enter new information.\n";
        

        cout << "\nSelect fields you want to update (Enter numbers separated by space):\n\n";
        cout << "1. Train Name\n";
        cout << "2. Source, Destination & Intermediate Stations\n";
        cout << "3. Running Days\n";
        cout << "4. Coach Classes & Seats\n";
        cout << "5. Exit\n";
        cout << "\nExample: 1 2 3\n";


        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string input;
        cout << "\nEnter your choice(s): ";
        getline(cin, input);


        stringstream ss(input);
        set<int> choices;
        int ch;

        while(ss >> ch){
            if(ch == 5){
                TrainList.clear();
                ReturnToAdminDashboard();
                return;
            }
            if(ch >= 1 && ch <= 4)
                choices.insert(ch);
        }

        string TrainName, Source, Destination;
        vector<string> UniqueDays;
        int TotalSeats = 0;
        pair<int,pair<int,int>> p;

        for(auto option : choices){

            switch(option){

                case 1:
                    TrainName = validator.getValidTrainName();
                    train.setTrainName(TrainName);
                    cout << "\n[UPDATED] Train Name\n"; 
                    break;

                case 2:

                    cout << "\n[INFO] Existing route & stoppages will be reset.\n";

                    while(true){
                        Source = validator.getValidStation("Source");
                        Destination = validator.getValidStation("Destination");
                        if(Source != Destination) break;
                        cout << "\n[ERROR] Source and Destination must be different.\n";
                    }
                    train.setSource(Source);
                    train.setDestination(Destination);

                    train.getStoppages().clear();
                    train.setStoppages(Source,0,1,0);
                    getValidStoppages(train);
                    break;


                case 3:

                    cout << "\n[INFO] Existing coach classes and seat configuration will be reset.\n";
                    getValidRunningDays(UniqueDays);
                    train.setRunningDays(UniqueDays);
                    cout << "\n[UPDATED] Running Days\n";
                    break;


                case 4:
                    train.getSeatsAvailablePerClass().clear();
                    getValidTrainClasses(train,TotalSeats);
                    train.setTotalSeats(TotalSeats);
                    train.setBookedSeats(0);
                    break;

            }

        }

        if(choices.empty()){
            TrainList.clear();
            ReturnToAdminDashboard();
            return;
        }

        /* ------------- CONFIRMATION ----------------- */
        cout << "\n[FINAL CONFIRMATION]\n";
        cout << "Selected updates will permanently overwrite existing train data.\n";

        string confirm;

        while (true) {

            cout << "\nDo you want to proceed? (Y/N): ";
            cin >> confirm;

            if (confirm == "Y" || confirm == "y") break;
            if (confirm == "N" || confirm == "n") {
                cout << "\n[INFO] Train update operation cancelled by Administrator.\n";
                TrainList.clear();
                ReturnToAdminDashboard();
                return;
            }

            cout << "\n[ERROR] Invalid input. Please enter 'Y' or 'N' only.\n";

        }


        /* ----------- SAVE CHANGES TO FILE ------------- */
        f.TruncateFile("D:\\Desktop\\trains.txt");
        f.SaveTrainsInfoToFile(TrainList);

        cout << "\n[SUCCESS] Train details updated successfully.\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        ReturnToAdminDashboard();

    }

    void ViewAllTrain(){

        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        if(TrainList.empty()){
            cout << "\n[INFO] No train services available.\n";
            ReturnToAdminDashboard();
            return;
        }

        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                INDIAN RAILWAYS - ADMIN PORTAL                                                     \n";
        cout << "                                                    VIEW ALL TRAIN SERVICE                                                         \n";
        cout << "===============================================================================================================================\n\n";
        

        cout << left
         << setw(5)  << "S.No"
         << setw(12) << "Train No"
         << setw(33) << "Train Name"
         << setw(50) << "Route"
         << setw(19) << "Days"
         << setw(7) << "Status"
         << endl;


        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        

        int index = 1;

        for(auto &t : TrainList){

            string route = t.getSource() + " -> " + t.getDestination();

            string days;
            if(t.getRunningDays().size() == 7) days = "Daily";
            else{
                for(auto &d : t.getRunningDays())
                    days += d + " ";
            }

            cout << left
                << setw(5)  << index++
                << setw(12) << t.getTrainNumber()
                << setw(33) << t.getTrainName()
                << setw(50) << route
                << setw(19) << days
                << setw(7) << "Active"
                << endl;
        }

        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        cout << "                            [INFO] Use \"View Train Details\" for complete route & fare information.                           ";
        cout << "\n===============================================================================================================================\n";
        

        TrainList.clear();
        ReturnToAdminDashboard();

    }

    void ViewTrainDetails(){

        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        if(TrainList.empty()){
            cout << "\n[INFO] No train services available.\n";
            ReturnToAdminDashboard();
            return;
        }


        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                INDIAN RAILWAYS - ADMIN PORTAL                                                 \n";
        cout << "                                                  VIEW TRAIN DETAILS SERVICE                                                   \n";
        cout << "===============================================================================================================================\n";
        

        /*------------ TRAIN NUMBER ------------*/
        int TrainNumber = validator.getValidTrainNumber();


        /*------------ CHECK WHETHER TRAIN EXISTS OR NOT ------------*/
        auto result = services.isTrainExist(TrainNumber,TrainList);
        bool exist = result.first;
        Train &train = *(result.second);

        if(!exist){
            cout << "\n[ERROR] Train service not found.\n";
            TrainList.clear();
            ReturnToAdminDashboard();
            return;
        }


        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        
        cout << "Train Number    : " << train.getTrainNumber() << endl;
        cout << "Train Name      : " << train.getTrainName() << endl;
        cout << "Route           : " << train.getSource()
            << " -> " << train.getDestination() << endl;

        cout << "Running Days    : ";
        if(train.getRunningDays().size() == 7) cout << "Daily";
        else{
            for(auto &d : train.getRunningDays())
                cout << d << " ";
        }
        cout << endl;

        cout << "Total Capacity  : " << train.getTotalSeats() << endl;
        cout << "Booked Seats    : " << train.getBookedSeats() << endl;

        /*---------- Classes ---------- */
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "CLASS & SEAT AVAILABILITY\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        
        cout << left << setw(15) << "Class" << setw(10) << "Seats" << endl;
        cout << "------------------------\n";

        for(auto &c : train.getSeatsAvailablePerClass()){
            cout << left << setw(15) << c.first
                << setw(10) << c.second << endl;
        }


        /* ------------- Stoppages ------------- */
        vector<pair<string, pair<int, pair<int,int>>>> vec;

        for(auto &s : train.getStoppages()){
            vec.push_back(s);
        }

        sort(vec.begin(), vec.end(),[](auto &a, auto &b){
                return a.second.second.first < b.second.second.first; // stop_no
            }
        );

    
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "ROUTE & STOPPAGES\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        
        cout << left
            << setw(8)  << "S.No"
            << setw(30) << "Station Name"
            << setw(30) << "Distance from Source(km)"
            << setw(25) << "Fare from Source(GN)" << endl;


        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        

        for(auto &s : vec){
            cout << left
                << setw(8)  << s.second.second.first
                << setw(30) << s.first
                << setw(30) << s.second.first
                << setw(25) << s.second.second.second
                << endl;
        }


        cout << "===============================================================================================================================\n";
        TrainList.clear();
        ReturnToAdminDashboard();

    }


    void TotalEarning(){


        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                    INDIAN RAILWAYS (IRCTC)                                                    \n";
        cout << "                                                    ADMINISTRATIVE CONSOLE                                                     \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                     TOTAL EARNINGS REPORT                                                     \n";
        cout << "===============================================================================================================================\n";


        unordered_map<long long, Ticket> BookedTickets = f.LoadTicketsFromFile();
        vector<pair<int,double>> CancelledTicketsCharges = f.LoadCancelledTicketsChargesFromFile();

        cout << "\n                                                      TRAIN WISE EARNINGS                                                      \n\n";
        cout << left << setw(12) << "Train No"
            << setw(28) << "No. of Booked Tickets"
            << setw(33) << "Total Booking Income(Rs)" << endl;

        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        

        unordered_map<int, pair<int,double>> TrainWiseBookingIncome; // {TrainNumber, TotalTickets, Price}
        unordered_map<int, pair<int,double>> TrainWiseCancellationIncome;
        double NetIncome = 0.0;


        /* ------------ CALCULATING THE TrainWiseBookingIncome -------------*/
        for(auto &entry : BookedTickets) {

            Ticket &ticket = entry.second;
            int trainNumber = ticket.getTrainNumber();
            double fare = ticket.getFare();
            int OldNoOfTickets = TrainWiseBookingIncome[trainNumber].first;
            double OldTotalFare = TrainWiseBookingIncome[trainNumber].second;

            TrainWiseBookingIncome[trainNumber] = {OldNoOfTickets+1,OldTotalFare+fare};

        }

        /* ------------ PRINTING THE TrainWiseBookingIncome -------------*/
        for(auto &x : TrainWiseBookingIncome){

            NetIncome += x.second.second;
            cout << left << setw(12) << x.first 
                << setw(28) << x.second.first
                << setw(33) << fixed << setprecision(2) << x.second.second << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        

        cout << "\n===============================================================================================================================\n";
        cout << "\n                                                     CANCELLATION EARNINGS                                                     \n\n";
        cout << left << setw(12) << "Train No"
            << setw(28) << "No. of Cancelled Tickets"
            << setw(33) << "Total Cancellation Income(Rs)" << endl;

        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        

        /* ------------ CALCULATING THE Cancellation Income -------------*/
        for(auto &entry : CancelledTicketsCharges) {

            int TrainNumber = entry.first;
            double Fare = entry.second;
            int OldNoOfTickets = TrainWiseCancellationIncome[TrainNumber].first;
            double OldTotalFare = TrainWiseCancellationIncome[TrainNumber].second;

            TrainWiseCancellationIncome[TrainNumber] = {OldNoOfTickets+1,OldTotalFare+Fare};

        }


        /* ------------ PRINTING THE Cancellation Income -------------*/
        for(auto &x : TrainWiseCancellationIncome){

            NetIncome += x.second.second;
            cout << left << setw(12) << x.first 
                << setw(28) << x.second.first
                << setw(33) << fixed << setprecision(2) << x.second.second << endl;
        }
        cout << "===============================================================================================================================\n\n";


        cout << "Net Income  : " << NetIncome << endl;
        
        cout << "\n===============================================================================================================================\n";
        cout << "                                   End of Earnings Report - For Internal Administrative Use                                    \n";
        cout << "                                          *** This is a System Generated Report ***                                            \n";
        cout << "===============================================================================================================================\n\n";


        BookedTickets.clear();
        CancelledTicketsCharges.clear();
        ReturnToAdminDashboard();

    }

};

class User{

    private:

    Files f;
    InputValidator validator;
    TrainService services;

    bool isValidRoute(Train &train, string src, string dst){

        auto stops = train.getStoppages();

        if(stops.find(src) == stops.end() || stops.find(dst) == stops.end())
            return false;

        return stops[src].second.first < stops[dst].second.first;
    }

    int getCurrentYear() {

        time_t now = time(0);
        tm *ltm = localtime(&now);
        return 1900 + ltm->tm_year;

    }


    bool isValidDate(int d, int m, int y) {

        int currentYear = getCurrentYear();
        if(y < currentYear || y > currentYear + 1){
            cout << "\n[ERROR] Invalid year";
            return false;
        }
        if(m < 1 || m > 12) return false;

        int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

        // Leap year check
        if(m == 2) {
            bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
            if(leap) daysInMonth[1] = 29;
        }

        if(d < 1 || d > daysInMonth[m-1]) return false;
        return true;

    }


    bool isPastDate(int d, int m, int y) {

        time_t now = time(0);
        tm *today = localtime(&now);

        int cd = today->tm_mday;
        int cm = today->tm_mon + 1;
        int cy = today->tm_year + 1900;

        // Compare dates
        if(y < cy) return true;
        if(y == cy && m < cm) return true;
        if(y == cy && m == cm && d < cd) return true;

        return false;

    }


    bool isWithinBookingWindow(int d, int m, int y) {

        time_t now = time(0);
        tm today = *localtime(&now);
        today.tm_hour = today.tm_min = today.tm_sec = 0;
        time_t todayTime = mktime(&today);

        tm journey = {};
        journey.tm_mday = d;
        journey.tm_mon  = m - 1;
        journey.tm_year = y - 1900;
        time_t journeyTime = mktime(&journey);

        double diffDays = difftime(journeyTime, todayTime) / (60 * 60 * 24);

        return (diffDays >= 0 && diffDays <= 120);

    }

    bool isTrainRunningOnDate(Train &train, int d, int m, int y) {

        string journeyDay = getDayFromDate(d, m, y);

        for(auto &day : train.getRunningDays()) {
            if(day == journeyDay)
                return true;
        }
        return false;

    }

    double getClassMultiplier(string &cls) {

        if(cls == "GN") return 1.0;
        if(cls == "2S") return 1.15;
        if(cls == "SL") return 1.25;
        if(cls == "3A") return 1.5;
        if(cls == "CC") return 1.75;
        if(cls == "2A") return 2.0;
        if(cls == "1A") return 2.5;

        return -1.0;

    }

    double calculateFare(Train &train, string &src, string &dst, string TrainClass){

        auto stops = train.getStoppages();
        int NormalFare = abs(stops[dst].second.second - stops[src].second.second);
        if(NormalFare == 0) NormalFare = 5;
        double FinalFare = double(NormalFare * getClassMultiplier(TrainClass));
        return FinalFare;

    }

    long long generatePNR() {

        unordered_map<long long, Ticket> BookedTickets = f.LoadTicketsFromFile();
        long long pnr;

        do {
            static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_int_distribution<int> firstDigit(1, 9);
            uniform_int_distribution<int> otherDigits(0, 9);

            string s = "";
            s += char('0' + firstDigit(rng));
            for(int i = 0; i < 9; i++)
                s += char('0' + otherDigits(rng));

            pnr = stoll(s);

        } while(BookedTickets.count(pnr));

        BookedTickets.clear();
        return pnr;
        
    }


    string getDayFromDate(int d, int m, int y) {

        tm time_in = {};
        time_in.tm_mday = d;
        time_in.tm_mon  = m - 1;
        time_in.tm_year = y - 1900;

        mktime(&time_in);

        string days[] = {"S","M","T","W","TH","F","SAT"};
        return days[time_in.tm_wday];

    }


    void getDateFromString(string &str, int &d, int &m, int &y){

        d = 0, m = 0, y = 0; // RESET

        int i=0;
        while(i<str.length() && str[i] != '-'){
            d = d*10 + (str[i++] - '0');
        }

        i++;

        while(i<str.length() && str[i] != '-'){
            m = m*10 + (str[i++] - '0');
        }

        i++;

        while(i<str.length()){
            y = y*10 + (str[i++] - '0');
        }

    }

    bool hasTrainClass(Train &train, string TrainClass){
        return train.getSeatsAvailablePerClass().count(TrainClass);
    }

    string fareStr(double f){

        if(f < 0) return "NA";

        stringstream ss;
        ss << fixed << setprecision(2) << f;
        return ss.str();

    }


    void printFareRow(Train &t, string Source, string Destination, int &idx){

        auto getFare = [&](string cls){
            if(!hasTrainClass(t,cls)) return string("NA");
            return fareStr(calculateFare(t, Source, Destination, cls));
        };

        cout << left << setw(8) << idx++
            << setw(13) << t.getTrainNumber()
            << setw(28) << Source
            << setw(28) << Destination
            << setw(8) << getFare("SL")
            << setw(8) << getFare("GN")
            << setw(8) << getFare("2S")
            << setw(8) << getFare("CC")
            << setw(8) << getFare("3A")
            << setw(8) << getFare("2A")
            << setw(8) << getFare("1A")
            << endl;
    }


    void ReturnToUserDashboard(){

        cout << "\n[INFO] Returning to User Dashboard...\n";
        cout << "Please wait...\n";
        cin.ignore();
        cout << "\nPress ENTER to continue...";
        cin.get();

    }


    public:

    void UserDashboard(){

        int choice;

        do{

            cout << "\n******************************************************** USER DASHBOARD *******************************************************\n";
            cout << "\n1. Book Ticket\n2. Cancel Ticket\n3. Check Seat Availability\n4. Find Train\n5. Print E-Ticket\n6. Train Information\n7. Logout\n";

            while(true){

                cout<<"\nEnter your Choice: ";
                cin>>choice;

                if(cin.fail() || choice > 7 || choice < 1){
                    cout << "\n[ERROR] Invalid menu option.\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    continue;
                }

                break;

            }
            
            switch(choice){

                case 1: BookTicket(); break;
                case 2: CancelTicket(); break;
                case 3: CheckSeatAvailability(); break;
                case 4: FindTrain(); break;
                case 5: PrintTicket(); break;
                case 6: TrainInformation(); break;
                case 7: break;
            }

        }while(choice != 7);


        cout << "\n\n===============================================================================================================================\n";
        cout << "                                     Thank you for using Indian Railways Passenger Services                                    \n";
        cout << "===============================================================================================================================\n";
       

    }


    void BookTicket(){

        Ticket ticket;
        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        if(TrainList.empty()){
            cout << "\n[INFO] No train services available...\n";
            ReturnToUserDashboard();
            return;
        }

        cout << "\n\n";
        cout << "===============================================================================================================================\n";
        cout << "                                                    INDIAN RAILWAYS (IRCTC)                                                    \n";
        cout << "                                                         USER SERVICES                                                         \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                 ONLINE TICKET BOOKING MODULE                                                  \n";
        cout << "===============================================================================================================================\n";
        
       
        /* --------------TRAIN NUMBER -------------- */
        int TrainNumber = validator.getValidTrainNumber();
        ticket.setTrainNumber(TrainNumber);


        /* ---------CHECK WHETHER TRAIN EXISTS OR NOT ----------- */
        auto result = services.isTrainExist(TrainNumber,TrainList); // {bool , vector<Train>::itertaor}
        bool exist = result.first;
        Train &train = *(result.second);


        if(!exist){
            cout << "\n[ERROR] Train not found.\n";
            TrainList.clear();
            ReturnToUserDashboard();
            return;
        }



        /* ---------- SOURCE & DESTINATION ---------- */
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string Source,Destination;

        while(true){

            Source = validator.getValidStation("Source");
            Destination = validator.getValidStation("Destination");

            if(Source != Destination) break;

            cout << "\n[ERROR] Source and Destination cannot be same.\n";
        }
        ticket.setRoute(Source,Destination);
        ticket.setTrainName(train.getTrainName());



        /* ----------- ROUTE VALIDATION ------------*/
        if(!isValidRoute(train, Source, Destination)){
            cout << "\n[ERROR] Invalid route for selected train.\n";
            TrainList.clear();
            ReturnToUserDashboard();
            return;
        }


        /* ------------ DATE OF JOURNEY ------------ */
        int d, m, y;
        char dash1, dash2;
        string DOJ = "";

        while(true) {

            cout << "\nEnter Date of Journey (DD-MM-YYYY): ";
            cin >> d >> dash1 >> m >> dash2 >> y;
            DOJ = to_string(d) + dash1 + to_string(m) + dash2 + to_string(y);


            if(cin.fail() || !isValidDate(d, m, y)) {
                cout << "\n[ERROR] Invalid date. Please enter a valid DOJ.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if(dash1 != '-' || dash2 != '-') {
                cout << "\n[ERROR] Date format must be DD-MM-YYYY\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if(isPastDate(d,m,y)){
                cout << "\n[ERROR] Date of Journey cannot be in the past.\n";
                cout << "[INFO] Please enter a future date.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if(!isWithinBookingWindow(d, m, y)) {
                cout << "\n[ERROR] Advance Reservation Period exceeded.";
                cout << "\nYou can book tickets only up to 120 days in advance.\n";
                continue;
            }

            if(!isTrainRunningOnDate(train, d, m, y)) {
                cout << "\n[ERROR] Train does not run on selected date.";
                cout << "\n[INFO] Train runs on: ";
                for(auto &day : train.getRunningDays())
                    cout << day << " ";
                cout << endl;
                continue;
            }

            break;
        }
        ticket.setDateOfJourney(DOJ);


        /* ----------- TICKET PRICE LIST OF SPECIFIED ROUTE ---------- */
        string TrainClass;

        cout << "\n\n-------------------------------------------- Ticket price list as per train coach ---------------------------------------------\n\n";
        cout << left << setw(8) << "Class"
            << setw(31) << "Ticket Price(Per Passenger)" << setw(19) << "Available Seats" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        

        for(auto &c : train.getSeatsAvailablePerClass()){
            TrainClass = c.first;
            cout << left << setw(8) << c.first
                << setw(31) << calculateFare(train,Source,Destination,TrainClass)
                << setw(19) << c.second << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        

        /* ---------- Class Selection ---------- */

        while(true){

            cout << "\nSelect Class: ";
            cin >> TrainClass;

            TrainClass = normalizeText(TrainClass);
            transform(TrainClass.begin(), TrainClass.end(), TrainClass.begin(), ::toupper);

            if(TrainClass.empty()){
                cout << "\n[ERROR] Input cannot be empty or spaces only.\n";
                continue;
            }

            if (train.getSeatsAvailablePerClass().count(TrainClass) == 0) {
                cout << "\n[ERROR] Invalid class selection.\n";
                continue;
            }

            ticket.setClass(TrainClass);
            break;
        }
        int availableSeats = train.getSeatsAvailablePerClass().at(TrainClass);
    

        /* --------------- NUMBER OF PASSENGERS --------------- */
        int passengerCount;

        while(true){

            cout << "\nNumber of Passengers: ";
            cin >> passengerCount;

            if(cin.fail() || passengerCount <= 0){
                cout << "\n[ERROR] Invalid passenger count.\n";
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                continue;
            }

            if(passengerCount > availableSeats){
                cout << "\n[ERROR] Insufficient seats available.\n";
                TrainList.clear();
                ReturnToUserDashboard();
                return;
            }

            ticket.setTotalPassengers(passengerCount);
            break;
        }


        /* ---------- Passenger Details ---------- */
        cout << "\n------------------------------------------------------ PASSENGER DETAILS ------------------------------------------------------\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<Passenger> passengers;
        Passenger p;

        for(int i = 0; i < passengerCount; i++){

            /* ---------  NAME INPUT --------- */

            while(true){

                cout << "\nPassenger " << i+1 << " Name: ";
                getline(cin, p.Name);
                p.Name = normalizeText(p.Name);

                if(p.Name.empty()){
                    cout << "\n[ERROR] Name cannot be empty.\n";
                    continue;
                }

                if(!validator.isValid(p.Name)){
                    cout << "\n[ERROR] Invalid name. Only alphabets and spaces allowed.\n";
                    continue;
                }
                break;
            }

            /* ----------- AGE INPUT ----------- */
            while(true){

                cout << "\nAge: ";
                cin >> p.Age;

                if(cin.fail() || p.Age <= 0){
                    cout << "\n[ERROR] Invalid age.\n";
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    continue;
                }
                break;

            }


            /*  ----------- GENDER INPUT ----------- */
            while (true) {

                cout << "\nGender (M/F): ";
                cin >> p.Gender;

                if(cin.fail() || p.Gender == ' '){
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cout << "\n[ERROR] Invalid input.\n";
                    continue;
                }

                p.Gender = toupper(p.Gender);

                if (p.Gender == 'M' || p.Gender == 'F' ) break;
                cout << "\n[ERROR] Please enter M or F only.\n";
            }

            passengers.push_back(p);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        ticket.setPassengers(passengers);


        /* ---------- Fare ---------- */
        double baseFare = calculateFare(train, Source, Destination, TrainClass);
        double totalFare = baseFare * passengerCount;

        ticket.setFare(totalFare);
        long long PNR = generatePNR();
        ticket.setPNR(PNR);
        

        /* -------- TICKET SUMMARY ----------*/
        cout << "\n======================================================= TICKET SUMMARY ========================================================\n";
        cout << "PNR                       : " << ticket.getPNR() << endl;
        cout << "Train                     : " << ticket.getTrainNumber() << " - " << ticket.getTrainName() << endl;
        cout << "Route                     : " << ticket.getSource() << " -> " << ticket.getDestination() << endl;
        cout << "Date of Journey           : " << ticket.getDateOfJourney() << endl;
        cout << "Class                     : " << ticket.getClass() << endl;
        cout << "Passengers                : " << ticket.getTotalPassengers() << endl;
        cout << "Base Fare (per passenger) : Rs " << fixed << setprecision(2) << baseFare<< endl;
        cout << "Total Fare                : Rs " << fixed << setprecision(2) << totalFare << endl;
        cout << "===============================================================================================================================\n";


        // ---------- Confirmation ----------
        int choice;
        cout << "\n1. Confirm & Proceed with Payment";
        cout << "\n2. Cancel Booking\n";

        while(true){

            cout << "\nEnter choice: ";
            cin >> choice;

            if(cin.fail() || choice <= 0 || choice > 2){
                cout << "\n[ERROR] Invalid menu option.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }

            if(choice == 2){
                cout << "\n[INFO] Booking Cancelled.\n";
                TrainList.clear();
                ReturnToUserDashboard();
                return;
            }

            break;
        }


        // ---------- Seat Update ----------
        int updatedSeats = availableSeats - passengerCount;
        train.setSeatsAvailablePerClass(TrainClass, updatedSeats);
        train.setBookedSeats(train.getBookedSeats()+passengerCount);


        /* ---------- FINAL SAVE ---------- */
        unordered_map<long long, Ticket> BookedTickets;
        BookedTickets[PNR] = ticket;
        f.SaveTicketsToFile(BookedTickets);

        f.TruncateFile("D:\\Desktop\\trains.txt");
        f.SaveTrainsInfoToFile(TrainList);
        

        cout << "\n[SUCCESS] Ticket booked successfully!\n";
        cout << "PNR Number : " << ticket.getPNR() << endl;
        cout << "===============================================================================================================================\n\n";
        ReturnToUserDashboard();

    }


    void CancelTicket(){

        unordered_map<long long, Ticket> BookedTickets = f.LoadTicketsFromFile();
        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        cout << "\n\n";
        cout << "===============================================================================================================================\n";
        cout << "                                                    INDIAN RAILWAYS (IRCTC)                                                    \n";
        cout << "                                                         USER SERVICES                                                         \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                  TICKET CANCELLATION MODULE                                                   \n";
        cout << "===============================================================================================================================\n";
        

        
        /* ------------  PNR INPUT ------------ */
        long long PNR;

        while(true){

            cout << "\nEnter PNR (10 Digits): ";
            cin >> PNR;

            if(cin.fail() || PNR < 1000000000LL || PNR > 9999999999LL){
                cout << "\n[ERROR] Invalid PNR format.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            break;
        }


        /* ------------  CHECK WHETHER TICKET EXIST OR NOT -----------*/
        auto it = BookedTickets.find(PNR);

        if(it == BookedTickets.end()){

            cout << "\n[ERROR] No ticket found with given PNR.\n";
            TrainList.clear();
            BookedTickets.clear();
            ReturnToUserDashboard();
            return;

        }
        Ticket &ticket =  it->second; 

        /* -------- TICKET SUMMARY ----------*/
        cout << "\n======================================================== TICKET SUMMARY =======================================================\n";
        cout << "PNR              : " << ticket.getPNR() << endl;
        cout << "Train            : " << ticket.getTrainNumber() << " - " << ticket.getTrainName() << endl;
        cout << "Route            : " << ticket.getSource() << " -> " << ticket.getDestination() << endl;
        cout << "Date of Journey  : " << ticket.getDateOfJourney() << endl;
        cout << "Class            : " << ticket.getClass() << endl;
        cout << "Passengers       : " << ticket.getTotalPassengers() << endl;
        cout << "Fare Paid        : Rs " << fixed << setprecision(2) << ticket.getFare() << endl;
        cout << "===============================================================================================================================\n";
        

        string DOJ = ticket.getDateOfJourney();
        int d = 0,m = 0,y = 0;
        getDateFromString(DOJ,d,m,y);

        if(isPastDate(d,m,y)){
            cout << "\n[ERROR] The journey date (" << DOJ << ") has already passed.\n";
            cout << "[INFO] Ticket cancellation is not allowed after the journey date.\n";
            TrainList.clear();
            BookedTickets.clear();
            ReturnToUserDashboard();
            return;
        }


        /* --------- DELETION CONFIRMATION ---------*/
        string confirm;
        cout << "\n[WARNING] This action will permanently cancel the ticket.\n";
        cout << "Do you want to proceed? (Y/N): \n";

        while(true){

            cout << "\nEnter choice: ";
            cin>>confirm;

            transform(confirm.begin(),confirm.end(),confirm.begin(),::toupper);

            if(confirm == " "){
                cout<<"\n[ERROR] Input cannot be empty.\n";
                continue;
            }

            if(confirm == "N"){
                cout << "\n[INFO] Ticket cancellation aborted by user.\n";
                ReturnToUserDashboard();
                TrainList.clear();
                BookedTickets.clear();
                return;
            }

            if(confirm == "Y") break;

            cout << "\n[ERROR] Please enter Y or N only.\n";
        }


        /* --------- CHECK WHETHER TRAIN NUMBER CORESSPONDING TO TICKET IS CORRECT OR NOT ----------*/
        int TrainNumber = ticket.getTrainNumber();
        auto result = services.isTrainExist(TrainNumber,TrainList); // data = { bool , Train} ---- THIS WILL RETURN THE ITERATOR OF SPECIFIED TRAIN NUMBER
        bool exist = result.first;
        Train &train = *(result.second);

        if(!exist){
            cout << "\n[ERROR] Associated train not found. Data inconsistency.\n";
            TrainList.clear();
            BookedTickets.clear();
            ReturnToUserDashboard();
            return;
        }


        /* ----------- UPDATING THE TRAINS SEAT ----------- */  
        int TotalPassengers = ticket.getTotalPassengers();
        
        auto &classMap = train.getSeatsAvailablePerClass();
        classMap[ticket.getClass()] += TotalPassengers;

        int UpdatedBookedSeats = train.getBookedSeats() - TotalPassengers;

        if(UpdatedBookedSeats < 0){
            cout << "\n[ERROR] Booked Seats cannot be zero. Data inconsistency.\n";
            BookedTickets.clear();
            TrainList.clear();
            ReturnToUserDashboard();
            return;
        }
        
        train.setBookedSeats(UpdatedBookedSeats);

        /* ---------- REFUND CALCULATION ----------- */
        double CancelCharge = double(ticket.getFare() * 0.1);
        double refundAmount = ticket.getFare() - CancelCharge; // 10% deducted


        /* -------- DELETING THE TICKET FROM BOOKED TICKETS --------- */
        BookedTickets.erase(it);


        /* ------------- UPDATE THE FILES --------------*/
        f.TruncateFile("D:\\Desktop\\BookedTickets.txt");
        f.SaveTicketsToFile(BookedTickets);

        f.TruncateFile("D:\\Desktop\\Trains.txt");
        f.SaveTrainsInfoToFile(TrainList);

        
        vector<pair<int,double>> CancelledTicketsCharges;
        CancelledTicketsCharges.push_back({TrainNumber,CancelCharge});
        f.SaveCancelledTicketsChargesToFile(CancelledTicketsCharges);


        /* -------- CANCELLED MESSAGE ---------- */
        cout << "\n===============================================================================================================================";
        cout << "\n[SUCCESS] Ticket cancelled successfully.\n";


        /* --------- REFUND MESSAGE---------*/
        cout << "\nRefund Amount        : Rs. " << fixed << setprecision(2) << refundAmount << "\n";
        cout << "Cancellation Charges : " << fixed << setprecision(2) << CancelCharge << " (10% of total fare)\n";
        cout << "[INFO] Refund will be credited to original payment method.\n";
        ReturnToUserDashboard();

    }

    void CheckSeatAvailability(){

        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                    INDIAN RAILWAYS (IRCTC)                                                    \n";
        cout << "                                                         USER SERVICES                                                         \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                    CHECK SEAT AVAILABILITY                                                    \n";
        cout << "===============================================================================================================================\n\n";
        

        /* ------------ TRAIN NUMBER ----------- */
        int TrainNumber = validator.getValidTrainNumber();


        /* ---------- CHECK WHETHER TRAIN EXISTS OR NOT -------- */
        auto result = services.isTrainExist(TrainNumber,TrainList);
        bool exist = result.first;
        Train &train = *(result.second);

        if(!exist){
            cout << "\n[INFO] No train found with the given train number.\n";
            TrainList.clear();
            ReturnToUserDashboard();
            return;
        }


        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                   SEAT AVAILABILITY STATUS                                                      \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";

        cout << "Train Number      : " << train.getTrainNumber() << "\n";
        cout << "Train Name        : " << train.getTrainName() << "\n";
        
        for(auto &x : train.getSeatsAvailablePerClass()){
            cout << left << setw(18) << x.first << ": " << x.second << endl;
        }
        

        cout << "\n===============================================================================================================================\n";
        cout << "                                Availability status is subject to change at the time of booking                                    ";
        cout << "\n===============================================================================================================================\n\n";
        

        TrainList.clear();
        ReturnToUserDashboard();
 
    }


    void FindTrainHelper(string Source, string Destination, int TrainNumber, vector<Train> &ExactMatchTrains, vector<Train> &PartialMatchTrains){

        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        for(auto &train : TrainList){

            map<string,pair<int,pair<int,int>>> stoppage = train.getStoppages();

            if(train.getTrainNumber() == TrainNumber){
                ExactMatchTrains.push_back(train);
            }

            else if(stoppage.find(Source) != stoppage.end() && stoppage.find(Destination) != stoppage.end() 
        && stoppage[Source].second.first < stoppage[Destination].second.first){
                ExactMatchTrains.push_back(train);
            }

            else if(stoppage.find(Source) != stoppage.end() && stoppage.find(Destination) != stoppage.end() 
        && stoppage[Source].second.first > stoppage[Destination].second.first){
                continue;
            }

            else if(stoppage.find(Source) != stoppage.end() || stoppage.find(Destination) != stoppage.end()){
                PartialMatchTrains.push_back(train);
            }

        }

        TrainList.clear();

    }

    void PrintTrainList(const string &title, vector<Train> &list) {

        if (list.empty()){
            cout << "\n                                                  "<< title << "                                                               \n";
            cout << "\n[INFO] No trains available....\n";
            return;
        }

        cout << "===============================================================================================================================\n";
        cout << "\n                                                        "<< title << "                                                          \n";

        for (auto &t : list) {
            cout << "\nTrain No   : " << t.getTrainNumber() << "\n";
            cout << "Train Name : " << t.getTrainName() << "\n";
            cout << "Route      : " << t.getSource()
                << " -> " << t.getDestination() << "\n";

            cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        }
        cout << endl;

    }


    void FindTrain(){

        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                      INDIAN RAILWAYS (IRCTC)                                                      \n";
        cout << "                                                          USER SERVICES                                                            \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                        FIND TRAIN MODULE                                                          \n";
        cout << "===============================================================================================================================\n\n";

        int choice, TrainNumber;
        string Source = "", Destination = "";
        vector<Train> ExactMatchTrains, PartialMatchTrains;

        cout << "\n1. Search by Source & Destination\n2. Search by Train Number\n";
        
        while(true){

            cout<<"\nEnter your choice: ";
            cin>>choice;

            if(cin.fail() || choice > 2 || choice < 1){
                cout << "\n[ERROR] Invalid menu option.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            break;
        }


        switch(choice){

            case 1:{

                cin.ignore();

                while(true){

                    Source = validator.getValidStation("Source");
                    Destination = validator.getValidStation("Destination");

                    if(Source != Destination) break;
                    cout << "[ERROR] Source and Destination must be different.";
                    
                }

                FindTrainHelper(Source,Destination,-1,ExactMatchTrains,PartialMatchTrains);
                PrintTrainList("Exact Match Trains",ExactMatchTrains);
                PrintTrainList("Partial Match Trains",PartialMatchTrains);

                break;
            }

            case 2:{

                TrainNumber = validator.getValidTrainNumber();
                FindTrainHelper("","",TrainNumber,ExactMatchTrains,PartialMatchTrains);
                PrintTrainList("Exact Match Trains",ExactMatchTrains);
                PrintTrainList("Partial Match Trains",PartialMatchTrains);
    
            }

        }


        cout << "\n========================================================= FARE DETAILS ========================================================\n\n";

        cout << left << setw(8) << "S.No"
            << setw(13) << "Train No."
            << setw(28) << "From"
            << setw(28) << "To"
            << setw(8) << "SL"
            << setw(8) << "GN"
            << setw(8) << "2S"
            << setw(8) << "CC"
            << setw(8) << "3A"
            << setw(8) << "2A"
            << setw(8) << "1A" << endl;


        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";

        int idx = 1;

        if(!ExactMatchTrains.empty()){
            cout << "[EXACT ROUTE MATCH TRAINS]\n\n";
            for(auto &t : ExactMatchTrains){
                if(Source.empty() && Destination.empty()) printFareRow(t, t.getSource(), t.getDestination(), idx);// if source and destination is empty...it means user have choosed train no option so for that, print the fare details according to train source and destination.
                else printFareRow(t, Source, Destination, idx);
            }
        }


        if(!PartialMatchTrains.empty()){
            cout << "\n[PARTIAL ROUTE MATCH TRAINS]\n\n";
            for(auto &t : PartialMatchTrains){
                string src, dst;
                if(Source.empty() && Destination.empty()) { src = t.getSource(); dst = t.getDestination(); }
                else{
                    if(t.getStoppages().count(Source)){
                        dst = t.getDestination();
                        src = Source;
                    }
                    else if(t.getStoppages().count(Destination)){
                        dst = Destination;
                        src = t.getSource();
                    }
                }
                printFareRow(t, src, dst, idx);
            }
        }

        
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n                                             [INFO] Fare shown is indicative only.                                              \n";
        cout << "===============================================================================================================================\n";
        ReturnToUserDashboard();

    }


    void PrintTicket(){

        unordered_map<long long, Ticket> BookedTickets = f.LoadTicketsFromFile();

        /* ------------  PNR INPUT ------------ */
        long long PNR;
        
        while(true){

            cout << "Enter PNR (10 Digits): ";
            cin >> PNR;

            if(cin.fail() || PNR < 1000000000LL || PNR > 9999999999LL){
                cout << "\n[ERROR] Invalid PNR format.\n\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            break;
        }

        auto it = BookedTickets.find(PNR);

        if(it == BookedTickets.end()){
            cout << "\n[ERROR] No ticket found with given PNR.\n";
            BookedTickets.clear();
            ReturnToUserDashboard();
            return;
        }

        Ticket &ticket = it->second;


        cout << "\n|====================================================================|";
        cout << "\n|                          INDIAN RAILWAYS                           |";
        cout << "\n|                        E-TICKET (CONFIRMED)                        |";
        cout << "\n|====================================================================|\n";
        cout << "| PNR Number        : " << left << setw(47) << ticket.getPNR() << "|\n";
        cout << "| Train No / Name   : " << left << setw(47) << (to_string(ticket.getTrainNumber()) + " - " + ticket.getTrainName()) << "|\n";
        cout << "| Date Of Journey   : " << left << setw(47) << ticket.getDateOfJourney() << "|\n";
        cout << "| From              : " << left << setw(47) << ticket.getSource() << "|\n";
        cout << "| To                : " << left << setw(47) << ticket.getDestination() << "|\n";
        cout << "| Class             : " << left << setw(47) << ticket.getClass() << "|\n";
        cout << "| Passenger Count   : " << left << setw(47) << ticket.getPassengers().size() << "|";
        cout << "\n|                                                                    |";
        cout << "\n|--------------------------------------------------------------------|";
        cout << "\n| Passenger Details                                                  |";
        cout << "\n|--------------------------------------------------------------------|";
        cout << "\n|                                                                    |";

        cout << left << "\n| " << setw(8) << "S.No" << "  "
            << setw(34) << "Name" << "  "
            << setw(7) << "Age" << "  "
            << setw(10) << "Gender" << "  |";


        cout << "\n|--------------------------------------------------------------------|\n";

        int idx = 1;
        for(auto &p : ticket.getPassengers()) {

            cout << "| "
                << setw(8) << left << idx++
                << "| "
                << setw(34) << left << p.Name
                << "| "
                << setw(7) << left << p.Age
                << "| "
                << setw(10) << left << p.Gender
                << "  |\n";
        }


        cout << "|--------------------------------------------------------------------|\n";
        cout << "| Total Fare       : Rs "
            << setw(45) << fixed << setprecision(2) << ticket.getFare() << "|\n";
        cout << "| Booking Status   : "
            << setw(48) << "CONFIRMED" << "|";

        cout << "\n|====================================================================|";
        cout << "\n|                Have a safe and pleasant journey :)                 |";
        cout << "\n|                       o!o Jai Jagannath o!o                        |";
        cout << "\n|====================================================================|\n\n";

        BookedTickets.clear();
        ReturnToUserDashboard();

    }


    void TrainInformation(){

        vector<Train> TrainList = f.LoadTrainsInfoFromFile();

        if(TrainList.empty()){
            cout << "\n[INFO] No train services available.\n";
            ReturnToUserDashboard();
            return;
        }

        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                    INDIAN RAILWAYS (IRCTC)                                                    \n";
        cout << "                                                         USER SERVICES                                                         \n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                   TRAIN INFORMATION MODULE                                                    \n";
        cout << "===============================================================================================================================\n\n";
                

        /*------------ TRAIN NUMBER ------------*/
        int TrainNumber = validator.getValidTrainNumber();


        /*------------ CHECK WHETHER TRAIN EXISTS OR NOT ------------*/
        auto result = services.isTrainExist(TrainNumber,TrainList);
        bool exist = result.first;
        Train &train = *(result.second);

        if(!exist){
            cout << "\n[ERROR] Train service not found.\n";
            TrainList.clear();
            ReturnToUserDashboard();
            return;
        }


        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";

        cout << "Train Number    : " << train.getTrainNumber() << endl;
        cout << "Train Name      : " << train.getTrainName() << endl;
        cout << "Route           : " << train.getSource()
            << " -> " << train.getDestination() << endl;

        cout << "Running Days    : ";
        if(train.getRunningDays().size() == 7) cout << "Daily";
        else{
            for(auto &d : train.getRunningDays())
                cout << d << " ";
        }
        cout << endl;


        /* ------------- Stoppages ------------- */
        vector<pair<string, pair<int, pair<int,int>>>> vec;

        for(auto &s : train.getStoppages()){
            vec.push_back(s);
        }

        sort(vec.begin(), vec.end(),[](auto &a, auto &b){
                return a.second.second.first < b.second.second.first; // stop_no
            }
        );


        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "ROUTE & STOPPAGES\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";

        cout << left
            << setw(8)  << "S.No"
            << setw(30) << "Station Name"
            << setw(30) << "Distance from Source(Km)" << endl;


        cout << "-------------------------------------------------------------------------------------------------------------------------------\n\n";
        
        for(auto &s : vec){
            cout << left
                << setw(8)  << s.second.second.first
                << setw(30) << s.first
                << setw(30) << s.second.first << endl;
        }


        cout << "\n[INFO] Fare is calculated based on distance and selected class.\n";
        cout << "===============================================================================================================================\n";
        TrainList.clear();
        ReturnToUserDashboard();

    }


};


class Authorization{

    private:
    Files f;

    bool isValidUserName(const string& username){

        if(username.length() < 6 || username.length() > 20)
            return false;

        if(!isalpha((unsigned char)username[0]))
            return false;

        if(username.back() == '.' || username.back() == '_')
            return false;

        for(char ch : username){
            if(!(isalnum((unsigned char)ch) || ch == '_' || ch == '.'))
                return false;
        }

        return true;

    }

    bool isValidPassword(const string &password){

        if(password.length() < 8 || password.length() > 20){
            cout << "\n[ERROR] Password must be 8 to 20 characters long.\n";
            return false;
        }

        bool hasUpper = false;
        bool hasLower = false;
        bool hasDigit = false;
        bool hasSpecial = false;

        string specialChars = "@#$%&!_";

        for(char ch : password){

            if(isspace((unsigned char)ch)){
                cout << "\n[ERROR] Password must not contain spaces.\n";
                return false;
            }

            if(isupper((unsigned char)ch)) hasUpper = true;
            else if(islower((unsigned char)ch)) hasLower = true;
            else if(isdigit((unsigned char)ch)) hasDigit = true;
            else if(specialChars.find(ch) != string::npos) hasSpecial = true;
            else{
                cout << "\n[ERROR] Invalid character used in password.\n";
                return false;
            }
        }


        if(!hasUpper){
            cout << "\n[ERROR] Password must contain at least one uppercase letter.\n";
            return false;
        }
        if(!hasLower){
            cout << "\n[ERROR] Password must contain at least one lowercase letter.\n";
            return false;
        }
        if(!hasDigit){
            cout << "\n[ERROR] Password must contain at least one digit.\n";
            return false;
        }
        if(!hasSpecial){
            cout << "\n[ERROR] Password must contain at least one special character (@#$%&!_).\n";
            return false;
        }

        return true;

    }

    void RedirectToUserDashboard(){

        cout << "\nRedirecting to User Dashboard...\n";
        cout << "Please wait...\n";
        cout << "\nPress ENTER to continue....";
        cin.get();

    }


    public:

    void AdminLogin(){

        const string ADMIN_ID = "admin";
        const string ADMIN_PASS = "admin@123";
        string adminId, password;
        int attempts = 3;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n********************************************************* ADMIN LOGIN *********************************************************\n";

        while(attempts > 0){

            /* -------- ADMINID INPUT ----------- */
            while(true){

                cout << "\nEnter Admin ID: ";
                getline(cin, adminId);

                if(adminId.empty()){
                    cout << "\n[ERROR] AdminId cannot be empty.\n";
                    continue;
                }
                
                break;
            }


            /* ----------- PASSWORD INPUT ------------ */  
            while(true){

                cout << "\nEnter Password: ";
                getline(cin, password);

                if(password.empty()){
                    cout << "\n[ERROR] Password cannot be empty.\n";
                    continue;
                }
                
                break;
            }


            /* -------- AUTHENTICATION -------- */
            if(adminId == ADMIN_ID && password == ADMIN_PASS){
                cout << "\n===============================================================================================================================";
                cout << "\n[SUCCESS] Admin login successful.\n\n";
                cout << "\nRedirecting to Admin Dashboard...\n";
                cout << "Please wait...\n";
                cout << "\nPress ENTER to continue....\n";
                cin.get();
                Admin admin;
                admin.AdminDashboard();
                return;
            }
            else{
                attempts--;
                cout << "\n===============================================================================================================================";
                cout << "\n[ERROR] Invalid Admin ID or Password.";
                cout << "\nAttempts remaining: " << attempts << "\n";
                cout << "\nPress ENTER to continue....";
                cin.get();
            }

        }

        cout << "\n===============================================================================================================================";
        cout << "\n[SECURITY] Too many failed attempts. Try again later.\n\n";
    }

 
    void UserLogin(){

        string Username, Password;
        int attempts = 3;

        unordered_map<string, string> UsersCredentials = f.LoadUsersFromFile();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n********************************************************* USER LOGIN **********************************************************\n";

        while(attempts > 0){

            /* -------- USERNAME INPUT ----------- */
            while(true){

                cout<<"\nEnter UserName: ";
                getline(cin,Username);

                if(Username.empty()){
                    cout << "\n[ERROR] Username cannot be empty.\n";
                    continue;
                }
                
                break;
            }
            

            /* ----------- PASSWORD INPUT ------------ */
            while(true){

                cout<<"\nEnter Password: ";
                getline(cin,Password);

                if(Password.empty()){
                    cout << "\n[ERROR] Password cannot be empty.\n";
                    continue;
                }

                break;
            }

            /* -------- AUTHENTICATION -------- */
            if(UsersCredentials.find(Username) != UsersCredentials.end() && UsersCredentials[Username] == Password){
                cout << "\n===============================================================================================================================";
                cout << "\n[SUCCESS] Login successful.\n";
                UsersCredentials.clear();
                RedirectToUserDashboard();
                User user;
                user.UserDashboard();
                return;
            }
            else{
                attempts--;
                cout << "\n===============================================================================================================================";
                cout << "\n[ERROR] Invalid username or password.\n";
                cout << "Attempts remaining: " << attempts << "\n";
                cout << "\nPress ENTER to continue....";
                cin.get();
            }

        }

        UsersCredentials.clear();
        cout << "\n===============================================================================================================================";
        cout << "\n[SECURITY] Too many failed attempts. Try again later.\n\n";

    }

    void NewUserRegistration(){

        unordered_map<string, string> UsersCredentials = f.LoadUsersFromFile();
        string Username, Password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n**************************************************** NEW USER REGISTRATION ****************************************************\n";

        /* -------- USERNAME INPUT ----------- */
        while(true){

            cout<<"\nEnter Username: ";
            getline(cin,Username);

            if(!isValidUserName(Username)){

                cout << "\n--------------------------------------------------------------";
                cout << "\n[ERROR] Invalid Username\n";
                cout << "\nUsername rules: ";
                cout << "\n * Length must be between 6 to 20 characters.";
                cout << "\n * Must start with an alphabet (A-Z or a-z).";
                cout << "\n * Allowed characters:";
                cout << "\n  - Alphabets (A-Z, a-z)";
                cout << "\n  - Digits (0-9)";
                cout << "\n  - Dot (.)";
                cout << "\n  - Underscore (_)";
                cout << "\n * No spaces allowed.";
                cout << "\n * Username must not end with '.' or '_'.\n";
                cout << "\nExample: \n * rahul_123\n * amit.kumar\n * irctc_user01\n";
                continue;
            }

            if(UsersCredentials.find(Username) != UsersCredentials.end()){
                cout << "\n===============================================================================================================================";
                cout << "\n[ERROR] Username already registered.\n";
                cout << "Please choose a different username or login if you already have an account.\n";
                continue;
            }

            break;
        }

        /* ----------- PASSWORD INPUT ------------ */
        while(true){

            cout<<"\nEnter Password: ";
            getline(cin,Password);

            if(!isValidPassword(Password)){
                cout << "\nPassword Requirements:\n";
                cout << "--------------------------------------------------------------\n";
                cout << " * Length must be between 8 to 20 characters\n";
                cout << " * Must contain at least one uppercase letter (A-Z)\n";
                cout << " * Must contain at least one lowercase letter (a-z)\n";
                cout << " * Must contain at least one digit (0-9)\n";
                cout << " * Must contain at least one special character (@ # $ % & ! _)\n";
                cout << " * Spaces are not allowed\n";
                cout << "--------------------------------------------------------------\n";
                cout << "Example: Rail@2024\n";
                continue;
            }

            break;
        }
       
        /* --------- SAVING TO FILE ----------- */
        UsersCredentials.clear();
        UsersCredentials[Username] = Password;
        f.SaveUsersToFile(UsersCredentials);



        cout << "\n===============================================================================================================================";
        cout << "\n[SUCCESS] User Registration Completed Successfully.";
        cout << "\nYour IRCTC user account has been created.";


        cout << "\nRedirecting to User Login....";
        cout << "\nPlease login using your registered username and password.";
        cout << "\nPress ENTER to continue....\n";
        cin.get();
        UserLogin();
        
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        

    }

};

int main(){
    
    int choice;
    Authorization authorization;

    do{

        cout << "\n\n===============================================================================================================================\n";
        cout << "                                                    IRCTC - INDIAN RAILWAYS                                                    ";
        cout << "\n===============================================================================================================================\n";
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << " IMPORTANT INFORMATION:\n\n";
        cout << "  * Please keep your Login Credentials confidential.\n";
        cout << "  * Ticket booking is subject to seat availability.\n";
        cout << "  * Cancellation charges may apply as per IRCTC policy.\n";
        cout << "  * Seat availability shown in this system is NOT date-specific.\n";
        cout << "  * Seats depend only on Train and Class, not on Date of Journey.\n";
        cout << "  * Date of Journey is used only to validate train running and booking rules.\n";
        cout << "\n-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << " MENU OPTIONS\n";
        cout<<"\n  1. Admin Login\n  2. User Login\n  3. New User Registration\n  4. Exit Application\n";
        cout << "\n===============================================================================================================================\n\n";
        

        while(true){

            cout<<"\nEnter your choice: ";
            cin>>choice;

            if(cin.fail() || choice > 4 || choice < 1){
                cout << "\n[ERROR] Invalid menu option.\n";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                continue;
            }
            break;

        }

        switch(choice){

            case 1: authorization.AdminLogin(); break;
            case 2: authorization.UserLogin(); break;
            case 3: authorization.NewUserRegistration(); break;
            case 4: break;
        }


    }while(choice != 4);
    
    return 0;
}
