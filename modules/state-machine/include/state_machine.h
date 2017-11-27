/* 
 * Finite State Machine parent class written in c++11 for simple and robust event driven and state based applications.
 *
 * Written by Javier Barbadillo <javier.barbadillo@gmail.com>
 */
 
#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
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
	FSM(std::vector<std::string> states, std::string initialState, std::vector<std::string> events, std::vector<std::vector<std::string>> transitions);
    virtual ~FSM() {}

    void propagateEvent(const std::string& event);
    State* getStateByName(const std::string& name);
	std::string getCurrentState();
	bool startFSM();
	bool updateFSM();
	bool stopFSM();
    
    
protected:   
    State* _currentState = nullptr;
    int getStateIndex(const std::string& name);
    bool existsEvent(const std::string& event);
    bool checkValidStates();
private:
	bool setInitialState(const std::string& name);
	bool addTransition(const std::string&  source, const std::string& event, const std::string& target);
	std::vector<State*> _states;
	std::vector<std::string> _events;
    bool _started = false;
    State* _initialState = nullptr;
};
#endif //FSM_H