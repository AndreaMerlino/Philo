<h1>Philosophers</h1>
<figure>
  <img src="https://austingwalters.com/wp-content/uploads/2014/05/Dining_philosophers.png" width="800" height="800 alt=" 5 Philosophers">
  <figcaption><strong>In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them. </strong>
  <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem" target="_blank" > More info on Wikipedia.</a>
  </figcaption> 
</figure>
<h2>Overview: </h2> 
<h3> The 42 project philosophers </h3>
 <img src="img/42" width="400" height="300" alt=" 42 School">
<p> Here are the things you need to know if you want to succeed this assignment:</p>
<ul>
<li>One or more philosophers sit at a round table.</li>
<li>There is a large bowl of spaghetti in the middle of the table.</li>
<li> The philosophers alternatively eat, think, or sleep.</li>
<li> While they are eating, they are not thinking nor sleeping; while thinking,they are not eating nor sleeping; and, of course,while sleeping,they are not eating nor thinking.</li>
<li> There are also forks on the table. There are as many forks as philosophers.</li>
<li> Because serving and eating spaghetti with only one fork is very inconvenient,a philosopher takes their right and their left forks to eat, one in each hand.</li>
<li> When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.</li>
<li> Every philosopher needs to eat and should never starve.</li>
<li> Philosophers don’t speak with each other.</li>
<li> Philosophers don’t know if another philosopher is about to die.</li>
<li> No need to say that philosophers should avoid dying!</li>
</ul>
<h3>Global rules</h3>
<p>You have to write a program that has to comply with the following rules:</p>
<ul>
<li>Global variables are forbidden!</li>
<li>Your(s) program(s) should take the following arguments:</li>
<ol> 
  <li>number_of_philosophers</li>
  <li>time_to_die </li>
  <li>time_to_eat </li>
  <li>time_to_sleep</li>
 <li>number_of_times_each_philosopher_must_eat (optional) </li>
</ol>
  ◦ number_of_philosophers: The number of philosophers and also the number of forks. ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die. ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks. ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping. ◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies. • Each philosopher has a number ranging from 1 to number_of_philosophers. • Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philoso- pher number N + 1.
</ul>
