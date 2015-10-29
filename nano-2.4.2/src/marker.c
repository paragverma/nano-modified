void initmcarray(mcarray *p){
	p->head = NULL;
	p->tail = NULL;
}

int distance_origin(mcpositions *a){
    return a->xcor + a->ycor;
}

int mc_empty(mcarray *p){
    return (p->head == NULL ) && (p->tail == NULL);
}


void decrement_xcor_f_sl(mcarray *p, ssize_t yco, size_t xco){
    mcpositions *q = p->head;
     while(q != NULL){
         if(q->ycor == yco)
            if(q->xcor > xco + 1) q->xcor--;
        q = q->next;
    }
    return;
}

void backspace_mc(mcarray *p){
	size_t x;
	ssize_t y;
        size_t x_orig = openfile->current_x;
	ssize_t y_orig = openfile->current_y;
	int i, j;
	int le;
        void *opts = NULL;
        int c_at_lastline = 0;
	mcpositions *q = p->head;
	linestruct *f = openfile->fileage;
        FILE *fp;
        fp = fopen("log.txt", "a");
        
        //decrement_xcor_f_sl(p, y_orig, x_orig);
	while(q != NULL){
            
		do_first_line();

		x = q->xcor--;
                q->x_shift--;
		y = q->ycor;

                fprintf(fp, "x is %d and y is %d\n", x, y);
                    for(j = 0; j < y; j++){
                        do_down_void();
                    }
                
                    for(i = 0; i < x; i++){
                        do_right();
                    }
                
                decrement_xcor_f_sl(p, y, x);
                do_deletion(REPLACE);
                //do_backspace();
                //do_deletion(INSERT);
                //do_deletion(CUT);
              q = q->next;
            }
        
        /*Move cursor to original position*/
        do_first_line();
                    for(j = 0; j < y_orig; j++){
                        do_down_void();
                    }
                    for(i = 0; i < x_orig; i++){
                        do_right();
                    }
                    for(i = 0; i < check_ycor_mcandcc(p, x_orig, y_orig); i++){
                        do_left();
                    }
        fclose(fp);
        return;
    
}
/*Add cursor position in a sorted way*/
void addposition(mcarray *p, size_t x, ssize_t y){
	mcpositions *q;
        mcpositions *r = p->head;
        mcpositions *r_f;
	q = (mcpositions*)malloc(sizeof(mcpositions));
	q->xcor = x;
	q->ycor = y;
        q->x_shift = 0;
	q->next = NULL;
	if(p->head == NULL && p->tail == NULL){
		p->head = q;
		p->tail = q;
		return;
	}
	
        while(r && (distance_origin(q) > distance_origin(r))){
            r_f = r;
            r = r->next;
        } 
        if(!r){
            p->tail->next = q;
            p->tail = q;
            return;
        }
        
        else if(r == p->head){
            q->next = p->head;
            p->head = q;
        }
        
        else {
            r_f->next = q;
            q->next = r;
        }
        
        
}

void freemcarray(mcarray *p){
	mcpositions *q = p->head;
	mcpositions *qtrail = q;
	
	while(q){
		q = q->next;
		free(qtrail);
		qtrail = q;
	}
	return;
}

/*Will return number of cursors placed in that line before the current cursor position*/
int check_ycor_mcandcc(mcarray *p, size_t x_orig, ssize_t y_orig){
    int i, j;
    int nofc = 0;
    mcpositions *q = p->head;
    
    while(q != NULL){
        if((q->ycor == y_orig) && (q->xcor < x_orig)) nofc++;
        q = q->next;
    }
    
    return nofc;
}
/*
q = (0,0) (1,1) (1,5)
c
0 1 2 3 4 5 6
  c       c       xco = 1, yco = 1  
0 1 2 3 4 5 6
0 1 2 3 4 5 6
0 1 2 3 4 5 6
0 1 2 3 4 5 6
 */
/*Increments xcors of all cursors in front the the current 
    cursor in the same line by 1*/
void increment_xcor_f_sl(mcarray *p, ssize_t yco, size_t xco){
    mcpositions *q = p->head;
     while(q != NULL){
         if(q->ycor == yco)
            if(q->xcor > xco + 1) q->xcor++;
        q = q->next;
    }
    return;
}

void printoptocursors(mcarray *p, size_t kbinput_len, char* output){
        FILE *fp;
	size_t x;
	ssize_t y;
        size_t x_orig = openfile->current_x;
	ssize_t y_orig = openfile->current_y;
	int i, j;
	int le;
        void *opts = NULL;
        int c_at_lastline = 0;
	mcpositions *q = p->head;
	linestruct *f = openfile->fileage;
        
        increment_xcor_f_sl(p, y_orig, x_orig);
	while(q != NULL){
            
		do_first_line();

		x = q->xcor++;
                q->x_shift++;
		y = q->ycor;


                    for(j = 0; j < y; j++){
                        do_down_void();
                    }
                
                    for(i = 0; i < x; i++){
                        do_right();
                    }
                
                increment_xcor_f_sl(p, y, x);

		do_output(output, kbinput_len, FALSE);

                
              q = q->next;
            }
        
        /*Move cursor to original position*/
        do_first_line();
                    for(j = 0; j < y_orig; j++){
                        do_down_void();
                    }
                    for(i = 0; i < x_orig; i++){
                        do_right();
                    }
                    for(i = 0; i < check_ycor_mcandcc(p, x_orig, y_orig); i++){
                        do_right();
                    }

        return;
}
