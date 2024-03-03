#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>
#include <ostream>

#include "../heap.h"  // Assuming your Heap implementation is in this location
#include "event.h"    // Includes Event and EventLess definitions
#include "gate.h"     // Includes Gate and Wire definitions

class Circuit {
public:
    Circuit();
    ~Circuit();
    void test();
    bool advance(std::ostream& os);
    void run(std::ostream& os);
    bool parse(const char* filename);
    void startUml(std::ostream& os);
    void endUml(std::ostream& os);
    
private:
    uint64_t m_current_time;
    std::vector<Gate*> m_gates;
    std::vector<Wire*> m_wires;
    
    // Min-heap of Event pointers, using EventLess as the comparator
    Heap<Event*, EventLess> m_pq;
};

#endif

// #ifndef CIRCUIT_H
// #define CIRCUIT_H
// #include <vector>

// #include "../heap.h"
// #include "event.h"
// #include "gate.h"

// class Circuit 
// {
// 	public:
// 		Circuit();
// 		~Circuit();
// 		void test();
// 		bool advance(std::ostream&);
// 		void run(std::ostream&);
//     bool parse(const char*);
//     void startUml(std::ostream&);
//     void endUml(std::ostream&);
		
// 	private:
// 		uint64_t m_current_time;
//     std::vector<Gate*> m_gates;
//     std::vector<Wire*> m_wires;
// 		// we need to add the m_pq data member. It should be a min-heap of Event*;
        
// };

// #endif
