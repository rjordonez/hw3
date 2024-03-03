#include <vector>
#include <random>
#include <iostream>

#include "gate.h"
#include "wire.h"

Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}

Gate::~Gate(){}

void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}

And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time) {
    // Default output state assumes both inputs are HIGH ('1')
    char newState = '1';

    // Iterate through inputs to determine the output state
    for (const auto& inputWire : m_inputs) {
        // Fetch the current state of each input wire
        char wireState = inputWire->getState();

        // If any input is LOW ('0'), output must be LOW ('0')
        if (wireState == '0') {
            newState = '0';
            break;
        }
        // If any input is unknown ('X'), output is unknown ('X')
        else if (wireState == 'X') {
            newState = 'X';
            // Continue checking other inputs as 'X' might turn to '0'
        }
    }

    // Check if the gate's output state has changed
    if (newState != m_current_state) {
        // Update the gate's current state
        m_current_state = newState;

        // Schedule the new state change event after the gate's delay
        return new Event{current_time + m_delay, m_output, newState};
    }

    // Return nullptr if there is no state change
    return nullptr;
}


Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* Or2Gate::update(uint64_t current_time)
{
    
  char state = '0';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '1')
		{
			state = '1';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
  if(state != m_current_state)
	{
    m_current_state = state;
		uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
  return e;
}


NotGate::NotGate(Wire* input, Wire* output) : Gate(1, output) {
    wireInput(0, input); 
}

Event* NotGate::update(uint64_t current_time) {
    char input_state = m_inputs[0]->getState();
    char new_state;

    // Define the NOT operation
    switch(input_state) {
        case '0': new_state = '1'; break;
        case '1': new_state = '0'; break;
        default: new_state = 'X';  
    }

    if (new_state != m_current_state) {
        m_current_state = new_state;
        uint64_t next_time = current_time + m_delay;
        auto e = new Event{next_time, m_output, new_state};  
        return e;
    }
    return nullptr;
}

