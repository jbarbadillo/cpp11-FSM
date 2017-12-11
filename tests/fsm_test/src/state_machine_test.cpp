#include <stdio.h>
#include <thread>
#include <math.h>

#include "state_machine.h"

#include "gtest/gtest.h"

struct StateMachinesTestParams{
    std::string initialState;
    std::vector<std::string> states;
    std::vector<std::string> events;

    StateMachinesTestParams(std::vector<std::string> states, std::vector<std::string> events, std::string initialState):
                states(states),events(events), initialState(initialState){}
};
class StateMachineTest : public ::testing::TestWithParam<StateMachinesTestParams>{
protected:
    std::string initialState;
    std::vector<std::string> states;
    std::vector<std::string> events;

    StateMachineTest(){
        StateMachinesTestParams const& p = GetParam();
        states = p.states;
        events = p.events;
        initialState = p.initialState;

    }
    virtual ~StateMachineTest(){

    }
    virtual void SetUp(){

    }
    virtual void TearDown(){

    }
public:
    void stateInit(){
        std::cout<< "STATE1" <<std::endl;
    }
    void stateStart(){
        std::cout<< "STATE2" <<std::endl;
    }
    void stateStop(){
        std::cout<< "STATE3" <<std::endl;
    }
};
TEST_P(StateMachineTest, InitializationTest){

    std::vector<std::vector<std::string>> transitions;
    transitions.push_back({"STATE1","next_event","STATE2"});
    transitions.push_back({"STATE2","next_event","STATE3"});
    transitions.push_back({"STATE3","next_event","STATE1"});
    transitions.push_back({"STATE3","next_event","STATE2"}); // will be rejected

    FSM* stateMachine = new FSM(states, initialState, events, transitions);

    bool started = stateMachine->startFSM();
    ASSERT_EQ(started, false);  

    stateMachine->getStateByName("STATE1")->run = std::bind(&StateMachineTest::stateInit, this);
    started = stateMachine->startFSM();
    ASSERT_EQ(started, false);
    stateMachine->getStateByName("STATE2")->run = std::bind(&StateMachineTest::stateStart, this);
    started = stateMachine->startFSM();
    ASSERT_EQ(started, false);
    stateMachine->getStateByName("STATE3")->run = std::bind(&StateMachineTest::stateStop, this);

    bool valid = stateMachine->updateFSM();
    ASSERT_EQ(valid, false);
    stateMachine->propagateEvent("next_event");


    started = stateMachine->startFSM();
    ASSERT_EQ(started, true);
}
TEST_P(StateMachineTest, RightUse){

    std::vector<std::vector<std::string>> transitions;
    transitions.push_back({"STATE1","next_event","STATE2"});
    transitions.push_back({"STATE2","next_event","STATE3"});
    transitions.push_back({"STATE3","next_event","STATE1"});

    FSM* stateMachine = new FSM(states, initialState, events, transitions);

    //Bind functions
    stateMachine->getStateByName("STATE1")->run = std::bind(&StateMachineTest::stateInit, this);
    stateMachine->getStateByName("STATE2")->run = std::bind(&StateMachineTest::stateStart, this);
    stateMachine->getStateByName("STATE3")->run = std::bind(&StateMachineTest::stateStop, this);

    bool res = stateMachine->startFSM();
    ASSERT_EQ(res, true);

    std::string cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState, initialState);

    //Cannot test it is protected
    //int index = stateMachine->getStateIndex(cState);
    //ASSERT_EQ(index, 0);

    stateMachine->propagateEvent("next_event");
    cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState, "STATE2");

    res = stateMachine->stopFSM();

    res = stateMachine->updateFSM();
    ASSERT_EQ(res, false);

    res = stateMachine->startFSM();
    ASSERT_EQ(res, true);
    cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState, "STATE2");


    stateMachine->propagateEvent("next_event");
    cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState, "STATE3");

    stateMachine->propagateEvent("next_event");
    cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState, "STATE1");

}

TEST_P(StateMachineTest, WrongOperations){
    //Initialize vectors of state machine
    std::vector<std::vector<std::string>> transitions;
    transitions.push_back({"STATE1","next_event","STATE2"});
    transitions.push_back({"STATE2","next_event","STATE3"});

    //Set initial state and try to start without setting valid transitions
    FSM* stateMachine = new FSM(states, initialState, events, transitions);
    bool res = stateMachine->startFSM();
    ASSERT_EQ(res, false);

    transitions.push_back({"STATE3","next_event","STATE1"});

    //Set initial state and try to start without setting valid initial state
    stateMachine = new FSM(states, "UNKNOWN", events, transitions);
    res = stateMachine->startFSM();
    ASSERT_EQ(res, false);

    //Add transitions. Now initialization is done correctly
    stateMachine = new FSM(states, initialState, events, transitions);

    stateMachine->getStateByName("STATE1")->run = std::bind(&StateMachineTest::stateInit, this);
    stateMachine->getStateByName("STATE2")->run = std::bind(&StateMachineTest::stateStart, this);
    stateMachine->getStateByName("STATE3")->run = std::bind(&StateMachineTest::stateStop, this);

    //Before start there is no current state
    std::string cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState,"");

    res = stateMachine->startFSM();
    ASSERT_EQ(res, true);

    //Before start there is no current state
    cState = stateMachine->getCurrentState();
    ASSERT_EQ(cState,initialState);

}

/*INSTANTIATE_TEST_CASE_P(Case1, StateMachineTest, ::testing::Values(
        
({"STATE1","STATE2","STATE3"},{"next_event"},"STATE1")
));*/
