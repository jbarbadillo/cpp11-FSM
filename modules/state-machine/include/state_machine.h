/* 
 * Written by Javier Barbadillo <jagmailvier.barbadillo@.com>
 */
 
#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <functional>

class FSM 
{
public:
	struct State{
        std::string name;
        std::map<std::string, State*> transitionMap;
        std::function<void()> run;

        State(std::string& name):
        name(name){

        }
    };
	std::vector<State*> _states;
    std::vector<std::string> _events;
    StateMachine(){}
    virtual ~StateMachine() {}

    bool addTransition(const std::string&  originName, const std::string& event, const std::string& stateName);
    void propagateEvent(const std::string& event);
    State* getStateByName(const std::string& name);
    bool setInitialState(const std::string& name);
    std::string getCurrentState();
    bool startSM();
    bool updateSM();
    bool stopSM();
protected:   
    State* _currentState = nullptr;
    int getStateIndex(const std::string& name);
    bool existsEvent(const std::string& event);
    bool checkValidStates();
private:
    bool _started = false;
    State* _initialState = nullptr;
};
#endif //FSM_H