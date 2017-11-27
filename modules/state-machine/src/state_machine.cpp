#include "state_machine.h"
#include <algorithm>
#include <iterator>

FSM::State* FSM::getStateByName(const std::string& name){
    auto it = std::find_if(_states.begin(), _states.end(), [=](State *  item){
        return name.compare(item->name)==0;
    });

    if(it != _states.end()){
        return *it;
    }else{
        return nullptr;
    }
}
int FSM::getStateIndex(const std::string& name){
    auto it = std::find_if(_states.begin(), _states.end(), [=](State *  item){
        return name.compare(item->name)==0;
    });
    if(it != _states.end()){
        return std::distance(_states.begin(), it);
    }else{
        return -1;
    }
}

bool FSM::existsEvent(const std::string& event){
    return std::find_if(_events.begin(),_events.end(), [=](std::string& item){
        return event.compare(item) == 0;
    }) != _events.end();
}
/**
 * @brief Adds transition to map if event and state are valid
 *
 * @param origin        Pointer to origin state
 * @param event         Name of event
 * @param stateName     Name of destini state
 * @return
 */
bool FSM::addTransition(const std::string&  originName, const std::string& event, const std::string& stateName){
    bool existsState = (getStateByName(stateName) != nullptr);
    bool existsOrigin = (getStateByName(originName) != nullptr);
    State* origin = getStateByName(originName);

    if(existsState && existsOrigin && existsEvent(event)){
        std::map<std::string,State*>::iterator i = origin->transitionMap.find(event);

        if (i == origin->transitionMap.end()) {
            origin->transitionMap[event]=getStateByName(stateName);
            return true;
        }else {
            return false;
        }
    }else{
        return false;
    }
}

void FSM::propagateEvent(const std::string& event){
    if(!_started){
        return;
    }
    std::map<std::string,State*>::iterator i = _currentState->transitionMap.find(event);

    if (i == _currentState->transitionMap.end()) {
        return;
    }else {
        _currentState =(i->second);
        _currentState->run();
        return;
    }
}
bool FSM::setInitialState(const std::string& name){
    if(getStateByName(name) != nullptr){
        _initialState = getStateByName(name);
        std::cout<<"StateMachine::initialState->"<< name.c_str() <<std::endl;
        return true;
    }
    return false;
}
std::string FSM::getCurrentState(){
    if(_currentState!=nullptr){
        return _currentState->name;
    }else{
        return "";
    }
}

bool FSM::startSM(){
    if(_initialState != nullptr &&  checkValidStates()){
        if(_currentState == nullptr){
            _currentState = _initialState;
        }
        std::cout<<"StateMachine::Started"<<std::endl;
        _currentState->run();
        _started = true;
        return true;
    }
    return false;
}
bool FSM::updateSM(){
    if(_currentState!=nullptr && _started){
        _currentState->run();
        return true;
    }
    return false;
}
bool FSM::stopSM(){
    if(_started){
        _started = false;
        std::cout<<"StateMachine::Stopped"<<std::endl;
        return true;
    }
    return false;
}

bool FSM::checkValidStates(){
    return std::find_if(_states.begin(),_states.end(), [=](State* state){
        bool invalid ((state->run == nullptr) || (state->transitionMap.size()<1));
        if (invalid) {
            std::cerr<<"StateMachine::Cannot Start! States not properly initialized"<<std::endl;
            std::cerr<<"StateMachine::Error at state "<< state->name.c_str()<<std::endl;
        }
        return invalid;
    }) == _states.end();
}