#include "retroosd.h"

//FIX ME DO CLEAN EXIT
//============================================================
//  constructor
//============================================================

mini_osd_interface::mini_osd_interface()
{
}


//============================================================
//  destructor
//============================================================

mini_osd_interface::~mini_osd_interface()
{
}


void mini_osd_interface::osd_exit(running_machine &machine)
{	
	write_log("osd_exit called \n");

	global_free(P1_device);
	global_free(P2_device);
	global_free(retrokbd_device);
	global_free(mouse_device);
}

void mini_osd_interface::init(running_machine &machine)
{
	int gamRot=0;

	osd_interface::init(machine);
	our_target = machine.render().target_alloc();

	initInput(machine);

	write_log("machine screen orientation: %s \n", (
		machine.system().flags & ORIENTATION_SWAP_XY) ? "VERTICAL" : "HORIZONTAL"
	);

        orient  = (machine.system().flags & ORIENTATION_MASK);
	vertical = (machine.system().flags & ORIENTATION_SWAP_XY);
        
        gamRot = (ROT270 == orient) ? 1 : gamRot;
        gamRot = (ROT180 == orient) ? 2 : gamRot;
        gamRot = (ROT90  == orient) ? 3 : gamRot;
        
	prep_retro_rotation(gamRot);

	write_log("osd init done\n");
}

bool draw_this_frame;

void mini_osd_interface::update(bool skip_redraw)
{
	//const render_primitive_list *primlist;
	UINT8 *surfptr;

	if(pauseg==-1){
		machine().schedule_exit();
		return;
	}

	if (FirstTimeUpdate == 1) {
		skip_redraw = 0; //force redraw to make sure the video texture is created
	}

	if (!skip_redraw) {

		draw_this_frame = true;
		// get the minimum width/height for the current layout
		int minwidth, minheight;
		//render_target_get_minimum_size(our_target, &minwidth, &minheight);
		our_target->compute_minimum_size(minwidth, minheight);

		if (FirstTimeUpdate == 1) {

			FirstTimeUpdate++;			
			write_log("game screen w=%i h=%i  rowPixels=%i\n", minwidth, minheight,minwidth );

			rtwi=minwidth;
			rthe=minheight;
			topw=minwidth;			

			int gamRot=0;
		        orient  = (machine().system().flags & ORIENTATION_MASK);
			vertical = (machine().system().flags & ORIENTATION_SWAP_XY);
        
		        gamRot = (ROT270 == orient) ? 1 : gamRot;
		        gamRot = (ROT180 == orient) ? 2 : gamRot;
		        gamRot = (ROT90  == orient) ? 3 : gamRot;
        
			prep_retro_rotation(gamRot);

		}

		if (minwidth != rtwi || minheight != rthe ){
			write_log("Res change: old(%d,%d) new(%d,%d) %d\n",rtwi,rthe,minwidth,minheight,topw);
			rtwi=minwidth;
			rthe=minheight;
			topw=minwidth;
		}

		// make that the size of our target
		our_target->set_bounds(rtwi,rthe);
		// get the list of primitives for the target at the current size
		render_primitive_list &primlist = our_target->get_primitives();

		// lock them, and then render them
		primlist.acquire_lock();

		surfptr = (UINT8 *) videoBuffer;

#ifdef M16B
software_renderer<UINT16, 3,2,3, 11,5,0>::draw_primitives(primlist, surfptr, minwidth, minheight,minwidth ); 
#else
software_renderer<UINT16, 3,2,3, 11,5,0>::draw_primitives(primlist, surfptr, minwidth, minheight,minwidth ); 
#endif

		primlist.release_lock();

		//co_switch(mainThread);
	} 
	else
    		draw_this_frame = false;

   co_switch(mainThread);
}  
 
 
//============================================================
//  update_audio_stream
//============================================================
void mini_osd_interface::update_audio_stream(const INT16 *buffer, int samples_this_frame) 
{
	audio_batch_cb(buffer, samples_this_frame);
}
  

//============================================================
//  set_mastervolume
//============================================================
void mini_osd_interface::set_mastervolume(int attenuation)
{
	// if we had actual sound output, we would adjust the global
	// volume in response to this function
}


//============================================================
//  customize_input_type_list
//============================================================
void mini_osd_interface::customize_input_type_list(simple_list<input_type_entry> &typelist)
{
	// This function is called on startup, before reading the
	// configuration from disk. Scan the list, and change the
	// default control mappings you want. It is quite possible
	// you won't need to change a thing.
}
 
