# Dynamic Planning in Games: the GOAP Approach

## Preface
This is a research project for [Steve Rabin's](http://www.aiwisdom.com/) AI course at [DigiPen Institute of Technology](https://www.digipen.edu/).

GOAP (Goal-Oriented Action Planning), was originally implemented by Jeff Orkin for the game F.E.A.R. during his time at Monolith Productions. GOAP is known for the emergent behavior that spawns from its simple components. At the root of the system is a Planner. Each planner has knowledge of the current worldstate in relation to its agent. Additionally, each planner can be customized by the user in two specific ways: setting a desired worldstate, and specifying a set of actions the planner can use to obtain this desired worldstate. All of these elements collectively are used during the pathing stage to obtain a set of actions the planner will enact to achieve its desired worldstate.

## Video Demonstration
A video demonstration can be found [here](https://www.youtube.com/watch?v=5ucnvGadaRg). The video is of our Sophomore year game project entitled "Genetic Drift". We had used our GOAP implementation to help create the game's AI.

## Research
The source code is paired with a research paper. This paper covers the thought process, functionality, pros and cons of our implementation, and the pros and cons of GOAP itself.

### References
+ [Applying Goal-Oriented Action Planning to Games](http://alumni.media.mit.edu/~jorkin/GOAP_draft_AIWisdom2_2003.pdf)
+ [Jeff Orkin's Website](http://alumni.media.mit.edu/~jorkin/)
+ [STRIPS Wikipedia Entry](https://en.wikipedia.org/wiki/STRIPS)
+ [GOAP Implementation Reference](https://github.com/stolk/GPGOAP)

## Contact
+ [Jordan Ellis](http://www.jordanellis.me) - j.ellis@digipen.edu
+ [Joshua Shlemmer](https://www.linkedin.com/pub/josh-shlemmer/96/625/3b9) - joshua.shlemmer@digipen.edu
