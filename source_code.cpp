#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include<cassert>
using namespace std;

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, string pick_up_location, string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    string getPickUpLocation() const {
        return pick_up_location;
    }

    string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(string location) {
        pick_up_location = location;
    }

    void setDropLocation(string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

    void print_trip(){
        //cout<<"Printing trip information"<<endl;
        ////cout<<"VehicleNumber : "<<vehicle->getVehicleNumber()<<endl;
        //cout<<"pick_up_location : "<<pick_up_location<<endl;
        //cout<<"departure_time : "<< departure_time <<endl;
        //cout<<"booked_seats : "<< booked_seats<<endl;
        //cout<<"------------------------------------------------------------------"<<endl;
    }
private:
    Vehicle* vehicle;
    string pick_up_location;
    string drop_location;
    int departure_time;
    int booked_seats;
};

//class BinaryTreeNode;

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};


class TransportService {
public:
    TransportService(string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    BinaryTreeNode * addNode(BinaryTreeNode * root, int key,Trip* trip){
        if(root==NULL){
            BinaryTreeNode * new_node= new BinaryTreeNode(key,trip);
            //this->setBSTHead(new_node);
            cout<<" adding node "<<endl;
            root=new_node;
            return new_node;
        }
        if(root->getDepartureTime()>key){
            root->setLeftPtr( addNode(root->getLeftPtr(),key,trip));
        }
        else{
            root->setRightPtr( addNode(root->getRightPtr(),key,trip));
        }
        return root;
    }

    BinaryTreeNode * searchNode(BinaryTreeNode * root,int key){
        if(root==NULL){
            return root;
        } 
        if(root->getDepartureTime()==key){
            return root;
        }
        else if(root->getDepartureTime()>key){
            return searchNode(root->getLeftPtr(),key);
        }
        else {
            return searchNode(root->getRightPtr(),key);
        }
    }

    BinaryTreeNode * searchNode_large(BinaryTreeNode * root, int key){
        BinaryTreeNode *temp = root;
        BinaryTreeNode *result = NULL;
        while (temp != NULL)
        {
            if (temp->getDepartureTime() == key)
            {
                return temp;
            }
            else if (temp->getDepartureTime() < key)
            {
                temp = temp->getRightPtr();
            }
            else if (temp->getDepartureTime() > key)            // left subtree 
            {
                result = temp;                                                      // this stores the value of just larger key
                temp = temp->getLeftPtr();
            }
        }
        
        return result;
        //return NULL;
    }

    BinaryTreeNode * deleteNode(BinaryTreeNode * root, int key){
        BinaryTreeNode * node=searchNode(root,key);
        if (node == NULL) {
            return root; // Node not found, nothing to delete
        }
        if(node->getLeftPtr()==NULL && node->getRightPtr()==NULL){       //leaf node
            BinaryTreeNode * parent=node->getParentPtr();
            if(parent!=NULL){
                if(parent->getLeftPtr()==node){
                    parent->setLeftPtr(NULL);
                }
                else{
                    parent->setRightPtr(NULL);
                }
            }
            delete node;
        }

        else if(node->getLeftPtr()==NULL || node->getRightPtr()==NULL){     // node with 1 child
            BinaryTreeNode * parent=node->getParentPtr();
            BinaryTreeNode * child=(node->getLeftPtr() != NULL) ? node->getLeftPtr() : node->getRightPtr();
            if (parent != NULL) {
                if (parent->getLeftPtr() == node) {
                    parent->setLeftPtr(child);
                } else {
                    parent->setRightPtr(child);
                }
            } else {
                root = child; // If the root node is deleted, update the root pointer
            }
            delete node; // Free the memory of the node
        }

        else{
            BinaryTreeNode * successor_node=successor(node->getRightPtr());
            node->setDepartureTime(successor_node->getDepartureTime());
            root = deleteNode(root, successor_node->getDepartureTime()); // Recursively delete the successor node     
        }
        return root;
    }

   

    BinaryTreeNode * findMin(BinaryTreeNode * root){
        if(root==NULL){
            return root;
        }
        return findMin(root->getLeftPtr());
    }

    BinaryTreeNode * successor(BinaryTreeNode * root){
        if(root==NULL){
            cout<<"line 261"<<endl;
            return root;
        }
        if(root->getRightPtr()!=NULL){
            cout<<"line 264"<<endl;
            return findMin(root->getRightPtr());
        }
        cout<<"line 267"<<endl;
        BinaryTreeNode * parent=root->getParentPtr();
        //assert(parent!=NULL);

        if (parent == NULL) {
        return NULL; // There is no in-order successor.
    }
        while(parent!=NULL && parent->getRightPtr()==root){
            root=parent;

            parent=parent->getParentPtr();
            cout<<"line 272"<<endl;
        }
        return parent;
    }

    void addTrip(int key, Trip* trip){
        //The service object creates a node for this trip and performs the node insert operation into the BST using the departure time as the key.
        BinaryTreeNode * node=this->addNode(BSThead,key, trip);
        this->setBSTHead(node);
    }

    void print_tree(BinaryTreeNode * root){
        if(root==NULL){
            return;
        }
        queue<BinaryTreeNode*> tree_node;
        tree_node.push(root);
        while(tree_node.size()!=0){
            BinaryTreeNode * front_node=tree_node.front();
            tree_node.pop();

            if(front_node!=NULL){
                
                cout<<front_node->getDepartureTime()<<" ";
                tree_node.push(front_node->getLeftPtr());
                tree_node.push(front_node->getRightPtr());
            }
            else{
                cout<<"-1 ";
            }
            
        }

    }

    int getHeight(BinaryTreeNode* root){
        if(root==NULL){
            return 0;
        }
        int left=getHeight(root->getLeftPtr());
        int right=getHeight(root->getRightPtr());
        return 1+left+right;
    }

private:
    string name;
    BinaryTreeNode* BSThead;
};

class Vehicle {
public:
    Vehicle(string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    void print_vehicle(){
        //cout<<"Info about vehicle"<<endl;
        //cout<<"Vehicle Number: "<<getVehicleNumber()<<endl;
        //cout<<"Seating capacity: "<<getSeatingCapacity()<<endl;
        //cout<<"Trips info"<<endl;
        for(int i=0;i<trips.size();i++){
            //cout<<"Trip number ["<<i+1<<"]"<<endl;
            //cout<<"BookedSeats: "<<trips[i]->getBookedSeats()<<"  DepartureTime: "<<trips[i]->getDepartureTime();
            //cout<<"  PickUpLocation: "<<trips[i]->getPickUpLocation()<<"  DropLocation: "<<trips[i]->getDropLocation()<<"  Vehicle number: "<<trips[i]->getVehicle()->getVehicleNumber()<<endl;
        }
        //cout<<"Printed vehicle object !"<<endl;
    }
private:
    string vehicle_number;
    int seating_capacity;
    vector<Trip*> trips;
};

class Location {
public:
    Location(string name) : name(name) {}

    // Getter functions
    string getName() const {
        return name;
    }
    TransportService* setServicePtr(std::string droplocation){
        TransportService * newly=new TransportService(droplocation);
        serviceptrs.push_back(newly);
        return newly;
    }

    TransportService* getServicePtr(string droplocation) {      // removed const
        for(int i=0;i<serviceptrs.size();i++){
            if(serviceptrs[i]->getName()==droplocation){
                return serviceptrs[i];
            }
        }
        TransportService* newService = setServicePtr(droplocation);
        return newService;
    }

    

    // Setter functions
    void setName(string location_name) {
        name = location_name;
    }



    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    
    vector<Trip*>  trip_vector(){
        return trips;
    }
     

    vector<TransportService* > serviceptrs_vector(){
        return serviceptrs;
    }

     void print_location(){
        //cout<<"Pick-up location: "<< name<<endl;
        //cout<<"Size of service ptr vector "<<serviceptrs.size()<<endl;
        for(int i=0;i<serviceptrs.size();i++){
            //cout<<serviceptrs[i]->getBSTHead();
        }
        //cout<<endl;
        for(int i=0;i<serviceptrs.size();i++){
            cout<<"-------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Corresponding drop-locations "<< serviceptrs[i]->getName()<<endl;
            ////cout<<"Depature times, all should be there "<<endl;
            BinaryTreeNode * root=serviceptrs[i]->getBSTHead();
            //cout<<"Head of tree corresponding to pickup drop location     "<<serviceptrs[i]->getBSTHead()<<endl;
            ////cout<<"Name of drop location : "<<serviceptrs[i]->getName()<<endl;
            serviceptrs[i]->print_tree(root);
            cout<<endl;
            cout<<"--------------Height of the tree is "<<serviceptrs[i]->getHeight(root)<<"--------------"<<endl;
            cout<<"-------------------------------------------------------------------------------------------------"<<endl;
            cout<<endl;
        }
        /*for(int i=0;i<trips.size();i++){
            //trips[i]->print_trip();
        }*/
     }
private:
    string name;
    vector<TransportService* >serviceptrs;
    vector<Trip*> trips;
};



class TravelDesk {
public:
    void addTrip(string vehicle_number, int seating_capacity, string pick_up_location, string drop_location, int departure_time) {
        // Implement this function to add a trip
        Vehicle * curr_vehicle=NULL;
        //check if the vehicle number mentioned in the trip is already there in the vehicle list.
        for(int i=0;i<vehicles.size();i++){
            if(vehicles[i]->getVehicleNumber()==vehicle_number){
                curr_vehicle=vehicles[i];
                break;
            }
        }
        
        //If not, a new vehicle object will be created and added to the vehicle list.
        if(curr_vehicle==NULL){
            curr_vehicle=new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(curr_vehicle);
        }

        //It then creates a trip object
        Trip * new_trip= new Trip(curr_vehicle,pick_up_location,drop_location,departure_time);

        //and (i) adds it to the vehicle object,
        curr_vehicle->addTrip(new_trip);
        
        cout<<"yes"<<endl;
        ////cout<<"Printing vehicle"<<endl;
        //curr_vehicle->print_vehicle();
        ////cout<<"Printing trip"<<endl;
       // new_trip->print_trip();

        //(i) adds it to the Location object associated with the pick-up location of the trip

        Location * curr_location= NULL;
        //cout<<"size of location vector  "<<locations.size()<<endl;

        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                ////cout<<pick_up_location<<"pick-up   "<<endl;
                ////cout<<"Pick up location address : "<<locations[i];
                curr_location=locations[i];
                curr_location->addTrip(new_trip);
                break;
            }
        } 
        if(curr_location==NULL){
            curr_location= new Location(pick_up_location);
            locations.push_back(curr_location);
            curr_location->addTrip(new_trip);
        }
        TransportService * head= curr_location->getServicePtr(drop_location);
        if(head->getBSTHead()==NULL){
            BinaryTreeNode * hi=new BinaryTreeNode(departure_time,new_trip);
            head->setBSTHead(hi);
        }

        else{
            cout<<head<<endl;
            head->addTrip(departure_time,new_trip);
        }
        curr_location->print_location();
        
    }


    vector<Trip*> showTrips(string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        vector<Trip*> required_trips;
        if(after_time>before_time){
            int temp=before_time;
            before_time=after_time;
            after_time=temp;
        }
        //This function will then identify the Location object for the location IITJ
        Location * curr_location= NULL;
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                curr_location=locations[i];
                break;
            }
        }
        if(curr_location==NULL){
            return {};
        }
        vector<Trip *> trip_vector=curr_location->trip_vector();
        for(int i=0;i<trip_vector.size();i++){
            int time=trip_vector[i]->getDepartureTime();
            if(time>=after_time && time<before_time){
                required_trips.push_back(trip_vector[i]);
            }
        }

        return required_trips; // Placeholder
    }


    vector<Trip*> showTripsbydestination(string pick_up_location, string destination,int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        vector<Trip*> required_trips;
        if(after_time>before_time){
            int temp=before_time;
            before_time=after_time;
            after_time=temp;
        }
        //This function will then identify the Location object for the location IITJ
        Location * curr_location= NULL;
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                curr_location=locations[i];
                break;
            }
        }
        //assert(curr_location==NULL);
        if(curr_location==NULL){
            cout<<"Location is null"<<endl;
            return {};
        }
        //and select the transport Service object that corresponds to the destination Poata.
        TransportService * transport= curr_location->getServicePtr(destination);

        if (transport == NULL) {
            return {};
        }
        cout<<"line 628"<<endl;
        //The BST in the Transport Service object is then checked for nodes that depict trips with departure times in the time range specified by the user.
        cout<<transport<<endl;
        cout<<transport->getBSTHead()<<endl;
        cout<<"Height : "<<transport->getHeight(transport->getBSTHead())<<endl;
        BinaryTreeNode * tree_root=transport->getBSTHead();
        transport->print_tree(tree_root);
        cout<<endl;
        //cout<<transport->searchNode_large(tree_root,after_time);
        //cout<<"error "<<flush;
        BinaryTreeNode * node_location=transport->searchNode_large(tree_root,after_time);
        cout<<node_location->getDepartureTime()<<endl;
        assert(node_location!=NULL);
        BinaryTreeNode * node_temp=node_location;
        cout<<node_temp<<endl;
        cout<<"Line 590+++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
        int i=0;
        while(node_temp!=NULL && node_temp->getDepartureTime()<before_time ){
            required_trips.push_back(node_temp->getTripNodePtr());
            int time=node_temp->getDepartureTime();
            cout<<node_temp->getDepartureTime()<<endl;
            //assert(node_temp->getParentPtr()!=NULL);
            
            cout<<"size of vector : "<<required_trips.size()<<endl;
            cout<<required_trips.front()->getDepartureTime()<<endl;
            //BinaryTreeNode * a=transport->successor(node_temp);
            //assert(a!=NULL);
            cout<<i<<flush;
            node_temp=transport->searchNode(tree_root,1000);
            break;
            /*if(node_temp->getRightPtr()!=NULL){
                node_temp=node_temp->getRightPtr();
            }else{
                node_temp=transport->successor(node_temp);
            }*/
            //node_temp=transport->successor(node_temp);
            //assert(node_temp==NULL);
            //cout<<node_temp;
            //node_temp=transport->searchNode_large(tree_root,time);
            i++;
        }
        //cout<<i<<flush;
        cout<<"size "<<required_trips.size()<<endl;
        return required_trips; // Placeholder
    }


    Trip* bookTrip(string pick_up_location, string drop_location, string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        Location * curr_location= NULL;
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==pick_up_location){
                curr_location=locations[i];
                break;
            }
        }
        if(curr_location==NULL){
            return NULL;
        }
        
         vector<Trip*> trip_vector=curr_location->trip_vector();

         for(int i=0;i<trip_vector.size();i++){
            if(trip_vector[i]->getVehicle()->getVehicleNumber()==vehicle_number  && trip_vector[i]->getDepartureTime()==departure_time && trip_vector[i]->getDropLocation()==drop_location){
                int seats=trip_vector[i]->getBookedSeats();
                trip_vector[i]->setBookedSeats(seats+1);
                
                //cout<<"seats : ["<<trip_vector[i]->getBookedSeats()<<"]"<<endl;
                //cout<<trip_vector[i]->getVehicle()->getSeatingCapacity()<<endl;

                if(trip_vector[i]->getBookedSeats()>trip_vector[i]->getVehicle()->getSeatingCapacity()){
                    TransportService * node=curr_location->getServicePtr(drop_location);
                    BinaryTreeNode * head=node->getBSTHead();
                    node->deleteNode(head,departure_time);
                }
                return trip_vector[i];
            }

         }

        return NULL; // Placeholder
    }

    Location* getLocation(string location){
        for(int i=0;i<locations.size();i++){
            if(locations[i]->getName()==location){
                return locations[i];
            }
        }
        return NULL;
    }

private:
    vector<Vehicle*> vehicles;
    vector<Location*> locations;
};



class BinaryTree {
protected:
    BinaryTreeNode* root;
private:
    int height_BST(BinaryTreeNode * root) const{
        if(root==NULL){
            return 0;
        }
        int left_height=height_BST(root->getLeftPtr());
        int right_height=height_BST(root->getRightPtr());
        return (1+max(left_height,right_height));
    }

    int count_nodes(BinaryTreeNode * root) const{
        if(root==NULL){
            return 0;
        }
        int left_nodes=count_nodes(root->getLeftPtr());
        int right_nodes=count_nodes(root->getRightPtr());
        return (1+left_nodes+right_nodes);
    }
public:
    BinaryTree() : root(NULL) {}

    int getHeight() const {
        // Implement this function to return the height of the tree
        return height_BST(root); // Placeholder
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        //return 0; // Placeholder
        return count_nodes(root);
    }
};

class BinarySearchTree : public BinaryTree
{
private:
    BinaryTreeNode *minimum_key(BinaryTreeNode *root) const
    {
        if (root == NULL)
        {
            return NULL;
        }
        BinaryTreeNode *temp = root;
        while (temp->getLeftPtr() != NULL)
        {
            temp = temp->getLeftPtr();
        }
        return temp;
    }

    BinaryTreeNode *maximum_key(BinaryTreeNode *root) const
    {
        if (root == NULL)
        {
            return NULL;
        }
        BinaryTreeNode *temp = root;
        while (temp->getRightPtr() != NULL)
        {
            temp = temp->getRightPtr();
        }
        return temp;
    }

    BinaryTreeNode * delete_node(BinaryTreeNode * root, int key){
        if(root==NULL){
            return root;
        }
        if(root->getDepartureTime()>key){
            root->setLeftPtr( delete_node(root->getLeftPtr(),key));
        }
        else if(root->getDepartureTime()<key){
            root->setRightPtr( delete_node(root->getRightPtr(),key));
        }
        else{
            if(root->getLeftPtr()==NULL || root->getRightPtr()==NULL){                      // node has 0 or 1 child
                BinaryTreeNode * a=(root->getLeftPtr()!=NULL)? (root->getLeftPtr()):(root->getRightPtr());
                root=a;
                return root;
            }
            else{                                                                                                                     // node has two children
                BinaryTreeNode * temp=findSuccessor(root,key);
                root->setDepartureTime(temp->getDepartureTime());
                root->setRightPtr(delete_node(root->getRightPtr(), temp->getDepartureTime()));
                delete temp;
            }
        }
    }

public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        // Implement this function to return the element with the minimum key
        // return NULL; // Placeholder
        return minimum_key(root);
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement this function to return the element with the maximum key
        // return NULL; // Placeholder
        return maximum_key(root);
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        BinaryTreeNode *temp = root;
        BinaryTreeNode *result = NULL;
        while (temp != NULL)
        {
            if (temp->getDepartureTime() == key)
            {
                return temp;
            }
            else if (temp->getDepartureTime() < key)
            {
                temp = temp->getRightPtr();
            }
            else if (temp->getDepartureTime() > key)            // left subtree 
            {
                //result = temp;                                                      // this stores the value of just larger key
                temp = temp->getLeftPtr();
            }
        }
        
        //return result;
        return NULL;
        // Implement this function to search for a node with the given key or the next larger key
        // return NULL; // Placeholder
    }


    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the successor node of the given node
        if (node == NULL)
        {
            return NULL;
        }
        if (node->getRightPtr() != NULL)
        {
            node = node->getRightPtr();
            while (node->getLeftPtr() != NULL)
            {
                node = node->getLeftPtr();
            }
            return node;
        }

        // Case 2: If the node doesn't have a right subtree, backtrack to find the successor.
        BinaryTreeNode *successor = NULL;
        BinaryTreeNode *ancestor = root; // Assuming 'root' is a pointer to the root node of your tree.
        while (ancestor != NULL)
        {
            if (node->getDepartureTime() < ancestor->getDepartureTime())           // left subtree 
            {
                successor = ancestor;
                ancestor = ancestor->getLeftPtr();
            }
            else if (node->getDepartureTime() > ancestor->getDepartureTime())
            {
                ancestor = ancestor->getRightPtr();
            }
            else if(node->getDepartureTime()==ancestor->getDepartureTime()){
                break;
            }
        }

        return successor;

        // return NULL; // Placeholder
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        return findSuccessor(root, key);
    }

    BinaryTreeNode *findSuccessor(BinaryTreeNode *node, int key) const
    {
        BinaryTreeNode *successor = NULL;

        while (node != NULL)
        {
            if (key < node->getDepartureTime())
            {
                successor = node; // Update the potential successor.
                node = node->getLeftPtr();
            }
            else if (key > node->getDepartureTime())
            {
                node = node->getRightPtr();
            }
            else
            {
                // Node with the given key found, now find the successor.
                if (node->getRightPtr() != NULL)
                {
                    successor = findMin(node->getRightPtr()); // Successor is the minimum node in the right subtree.
                }
                break;
            }
        }

        return successor;
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        return findPredecessor(root, node);
    }


    BinaryTreeNode *findPredecessor(BinaryTreeNode *root, BinaryTreeNode *target) const
    {
        BinaryTreeNode *predecessor = NULL;
        BinaryTreeNode * temp=root;
        if (target->getLeftPtr() != NULL)
                {
                    predecessor = findMax(target->getLeftPtr()); // Predecessor is the maximum node in the left subtree.
                    return predecessor;
                }
        while (temp != NULL)
        {
            if (target->getDepartureTime() < temp->getDepartureTime())
            {
                temp = temp->getLeftPtr();
            }
            else if (target->getDepartureTime() > temp->getDepartureTime())
            {
                predecessor = temp; // Update the potential predecessor.
                temp= temp->getRightPtr();
            }
            else if(target->getDepartureTime() == temp->getDepartureTime()){
                break;
            }
        }

        return predecessor;
    }



    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        BinaryTreeNode *node = findNode(root, key); // Find the node with the given key.
        if (node == NULL)
        {
            return NULL; // Key not found.
        }
        return findPredecessor(root, node);
    }




    BinaryTreeNode *findNode(BinaryTreeNode *root, int key) const
    {
        while (root != NULL)
        {
            if (key < root->getDepartureTime())
            {
                root = root->getLeftPtr();
            }
            else if (key > root->getDepartureTime())
            {
                root = root->getRightPtr();
            }
            else
            {
                return root; // Node with the given key found.
            }
        }
        return NULL; // Key not found.
    }

    BinaryTreeNode *findMax(BinaryTreeNode *node) const
    {
        while (node->getRightPtr() != NULL)
        {
            node = node->getRightPtr();
        }
        return node;
    }

    BinaryTreeNode *findMin(BinaryTreeNode *node) const
    {
        while (node->getLeftPtr() != NULL)
        {
            node = node->getLeftPtr();
        }
        return node;
    }
};

