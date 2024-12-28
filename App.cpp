#include "App.h"
#include <algorithm>

// Constructor
App::App()
{}

// Adds a new profile
void App::addProfile(std::string name, int height, int weight){

    // Create a new user profile
    UserProfile* newProfile = new UserProfile(name, height, weight);

    // Add the new user profile to the users vector
    users.push_back(newProfile);
}

// Deletes a profile by name
void App::deleteProfile(std::string name){

    // Find the profile matching the name
    auto it = std::remove_if(users.begin(), users.end(), [&](UserProfile* profile){
        return profile->getName() == name;
    });

    // If profile with given name is found, delete it and remoce from the vector
    if (it != users.end()) {
        delete *it; // Free memory
        users.erase(it, users.end()); // Delete from the vector
    }
}

// Modifies profile at index num
void App::modifyProfile(int num, std::string name, int newHeight, int newWeight){
    users[num]->setName(name); // Update name
    users[num]->setHeight(newHeight); // Update height
    users[num]->setHeight(newWeight); // Update weight
}

std::vector<UserProfile*> App::getUsers(){
     return users;
}

// Checks if a user profile with the given name already exists
bool App::isDuplicate(std::string name){
    // Iterate through users
    for (UserProfile* profile : users) {
        // If profile is a duplicate return true
        if (profile->getName() == name) {
            return true;
        }
    }
    return false;
}

// Processes unprocessed data to return meaningful results
void App::processData(std::array<int, 24> unprocessedData, int currentUser) {

    // Initialize indicators and organ states
    Indicator indicators;
    std::vector<State> organs = {State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL, State::NORMAL};
    int organStats[7] = {1, 1, 2, 2, 1, 1, 1};

    // Iterate through each measurement point
    for (int i = 0; i < 24; ++i) {
        int value = unprocessedData[i]; // Current point

        // H1R-H6R, H1L-H6L, F1R-F6R, F1L-F6L
        // Hand
        if (i == 0 || i == 6) { // H1
            if (value > 85) {
                // H1: Stiff and painful shoulder muscles, rush of blood to the head, hot flashes, piles, asthma
                indicators.energy += 1;
                indicators.metabolism += 1;
                organStats[2]+=1;
            } else if (value < 55) {
                // H1: Cold feet or numbness, shortness of breath, coughing spells
                indicators.psychoemo -= 1;
                indicators.musculoskeletal -= 1;
                if(i == 0){
                    organStats[0]-=1;
                }
                else{
                    organStats[1]-=1;
                }
            }

        } else if (i == 1 || i == 7) { // H2
            if (value > 75) {
                // H2: Stiff and painful shoulder muscles, middle age level wrenched shoulders, brachial neuralgia
                indicators.musculoskeletal += 1;
                indicators.energy += 1;
            } else if (value < 55) {
                // H2: Palpitation, heated sensation of the palms
                indicators.psychoemo -= 1;
                indicators.immune -= 1;
                organStats[2]-=1;
            }

        } else if (i == 2 || i == 8) { // H3
            if (value > 65) {
                // H3: Puffed sensation of the stomach, constipation
                indicators.metabolism += 1;
                organStats[3]+=1;
                organStats[5]+=1;
                organStats[6]+=1;
            } else if (value < 45) {
                // H3: Palpitation
                indicators.psychoemo -= 1;
                organStats[2]-=1;
            }

        } else if (i == 3 || i == 9) { // H4
            if (value > 75) {
                // H4: Headaches, abnormalities of the lower abdomen, joint pain
                indicators.musculoskeletal += 1;
                indicators.metabolism += 1;
            } else if (value < 55) {
                // H4: Headache, abnormalities of the lower abdomen
                indicators.immune -= 1;
                indicators.psychoemo -= 1;
            }

        } else if (i == 4 || i == 10) { // H5
            if (value > 90) {
                // H5: Ringing ears, difficulty in hearing
                indicators.psychoemo += 1;
                if(i == 4){
                    organStats[0]+=1;
                }
                else{
                    organStats[1]+=1;
                }
            } else if (value < 60) {
                // H5: Tiredness or tendency to tire, the healthy glow disappears and body hairs increase in density
                indicators.energy -= 1;
                indicators.immune -= 1;
            }

        } else if (i == 5 || i == 11) { // H6
            if (value > 90) {
                // H6: Stiff and painful shoulder muscles, toothache
                indicators.musculoskeletal += 1;
                indicators.energy += 1;
            } else if (value < 60) {
                // H6: Stiff and painful shoulder muscles
                indicators.musculoskeletal -= 1;
            }
        }


        // Foot
        else if (i == 12 || i == 18) { // F1
            if (value > 70) {
                // F1: General weakness of the stomach, knee joint pain
                indicators.energy += 1;
                indicators.metabolism += 1;
                organStats[3]+=1;
            } else if (value < 50) {
                // F1: General weakness of stomach, abnormalities of the knee joint, insomnia, glycosuria
                indicators.psychoemo -= 1;
                indicators.immune -= 1;
                organStats[3]-=1;
                organStats[4]-=1;
            }

        } else if (i == 13 || i == 19) { // F2
            if (value > 60) {
                // F2: Insomnia, readily provoked, abnormalities in menstruation, lumbar pain
                indicators.psychoemo += 1;
                indicators.energy += 1;
            } else if (value < 40) {
                // F2: Faintness or dizziness on abrupt standing up (orthostatic circulatory disorder)
                indicators.musculoskeletal -= 1;
                organStats[2]+=1;
            }

        } else if (i == 14 || i == 20) { // F3
            if (value > 65) {
                // F3: Fretting and fuming, anxiety
                indicators.psychoemo+= 1;
            } else if (value < 45) {
                // F3: Loss of willingness to concentrate and general tiredness, coldness in hips and legs
                indicators.energy -= 1;
                indicators.metabolism -= 1;
            }

        } else if (i == 15 || i == 21) { // F4
            if (value > 65) {
                // F4: Stiff neck muscles, headaches, sciatic neuritis, lumbar pain
                indicators.musculoskeletal += 1;
            } else if (value < 45) {
                // F4: Stiffness and painful neck muscles, lumbar pain, dullness of the feet
                indicators.immune -= 1;
                indicators.psychoemo -= 1;
            }

        } else if (i == 16 || i == 22) { // F5
            if (value > 55) {
                // F5: Headaches
                indicators.energy += 1;
            } else if (value < 40) {
                // F5: Abnormalities of eyes, dizziness (Meniere's disease)
                indicators.immune -= 1;
                indicators.psychoemo -= 1;
            }

        } else if (i == 17 || i == 23) { // F6
            if (value > 60) {
                // F6: Anomalies of the joints, middle age wrenched shoulder, elbow neuralgia
                indicators.musculoskeletal +=1;
            } else if (value < 45) {
                // F6: Stiff and painful shoulder muscles, distention of stomach, bloating of face, yawning
                indicators.energy -= 1;
                indicators.psychoemo -= 1;
                organStats[3]-=1;
            }
        }

        //conclusions drawn from measurements of normalcy
        //Indicators:
        //Energy
            // Indicator value = 0, 1, 2 -> Below Normal
            // Indicator value = 3, 4, 5, 6 -> Normal
            // Indicator value = 7, 8, 9 -> Above Normal
        if(indicators.energy<3){
            indicators.states[0] = State::BELOWNORM;
        }
        else if (indicators.energy<7){
            indicators.states[0] = State::NORMAL;
        }
        else{
            indicators.states[0] = State::ABOVENORM;
        }
        //Immune
            // Indicator value = 0, 1, -> Below Normal
            // Indicator Value = 2, 3, 4 -> Normal
            // Indicator Value = 5, 6 -> Above Normal
        if(indicators.immune<2){
            indicators.states[1] = State::BELOWNORM;
        }
        else if (indicators.immune<5){
            indicators.states[1] = State::NORMAL;
        }
        else{
            indicators.states[1] = State::ABOVENORM;
        }
        //Metabolism:
            // Indicator value = 0, 1, -> Below Normal
            // Indicator Value = 2, 3 -> Normal
            // Indicator Value = 4, 5 -> Above Normal
        if(indicators.metabolism<2){
            indicators.states[2] = State::BELOWNORM;
        }
        else if (indicators.metabolism<4){
            indicators.states[2] = State::NORMAL;
        }
        else{
            indicators.states[2] = State::ABOVENORM;
        }
        //Psycho-emotional:
            // Indicator value = 0, 1, 2 -> Below Normal
            // Indicator Value = 3, 4, 5, 6, 7 -> Normal
            // Indicator Value = 8, 9, 10 -> Above Normal
        if(indicators.psychoemo<3){
            indicators.states[3] = State::BELOWNORM;
        }
        else if (indicators.psychoemo<8){
            indicators.states[3] = State::NORMAL;
        }
        else{
            indicators.states[3] = State::ABOVENORM;
        }
        //Musculoskeletal:
            // Indicator value = 0, 1, 2 -> Below Normal
            // Indicator value = 3, 4, 5 -> Normal
            // Indicator value = 6, 7, 8 -> Above Normal
        if(indicators.musculoskeletal<3){
            indicators.states[4] = State::BELOWNORM;
        }
        else if (indicators.musculoskeletal<6){
            indicators.states[4] = State::NORMAL;
        }
        else{
            indicators.states[4] = State::ABOVENORM;
        }

        //Organs
        //Lungs (Left AND Right): 0 = Below Normal, 1 = Normal, 2 = Above Normal
        if(organStats[0]<1){
             organs[0] = State::BELOWNORM;
        }
        else if (organStats[0]<2){
            organs[0] = State::NORMAL;
        }
        else{
            organs[0] = State::ABOVENORM;
        }

        if(organStats[1]<1){
             organs[1] = State::BELOWNORM;
        }
        else if (organStats[1]<2){
            organs[1] = State::NORMAL;
        }
        else{
            organs[1] = State::ABOVENORM;
        }
        //Heart: 0 = Below Normal, 1, 2, 3 = Normal, 4 = Above Normal
        if(organStats[2]<1){
             organs[2] = State::BELOWNORM;
        }
        else if (organStats[2]<2){
            organs[2] = State::NORMAL;
        }
        else{
            organs[2] = State::ABOVENORM;
        }
        //Stomach: 0 = Below Normal, 1, 2, 3 = Normal, 4 = Above Normal
        if(organStats[3]<1){
             organs[3] = State::BELOWNORM;
        }
        else if (organStats[3]<2){
            organs[3] = State::NORMAL;
        }
        else{
            organs[3] = State::ABOVENORM;
        }
        //Kidneys: 0 = Below Normal, 1=Normal
        if(organStats[4]<1){
             organs[4] = State::BELOWNORM;
        }
        else{
            organs[4] = State::NORMAL;
        }
        //Intestines: 0 = Below Normal, 1=Normal
        if(organStats[5]<1){
             organs[5] = State::BELOWNORM;
        }
        else{
            organs[5] = State::NORMAL;
        }
        if(organStats[6]<1){
             organs[6] = State::BELOWNORM;
        }
        else{
            organs[6] = State::NORMAL;
        }
    }

    // Calculate average for all indicators
    indicators.calculateAverage();

    // Create a new data object with processed data
    Data* data = new Data(indicators, organs);

    // Generate recommendations based on processed data
    data->generateRecommendation();

    // Add processed data to the user profile
    users[currentUser]->addData(*data);
}
