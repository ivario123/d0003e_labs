/*
 * ui.c
 *
 * Created: 2022-02-22 16:35:29
 *  Author: ivarj
 */ 
void init_app(app_object * self,pulse_gen *pulse_gens,uint8_t number_of_pulsegens){
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->current_pulsegen = 0;
	self->number_of_pulsegens = number_of_pulsegens;
	self->pulse_gens = pulse_gens;
}
void itterate_pulse_gen(app_object * self,int8_t dirrection){
	// gets the next pulse gen
	self->current_pulsegen=((int8_t)(self->current_pulsegen)+dirrection)%self->number_of_pulsegens;
	ASYNC(self,update_display,0);
}
void update_display(app_object * self, int arg){
		print_at(self->current_pulsegen,0,2);
		print_at((pulse_gens+self->current_pulsegen)->freq,4,2);
}