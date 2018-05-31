typedef struct {
	const char* mo_data;	
	bool reversed; // endianess
	bool language_is_right_to_left; // arabic
} LocalisationText;

LocalisationText* localisation_text_create(const char* folder, const char* language_name)
{
	data = read_entire_file(folder + language_name + ".mo");
	if (data.length < 24) { error("too short for .mo file"); } 

	localisation_text->mo_data = data;

	uint32_t* long_ptr = (uint32_t *)data;

	const uint32_t TARGET_MAGIC = 0x950412DE;
	const uint32_t TARGET_MAGIC_REVERSED = 0xDE120495;

	uint32_t magic = *long_ptr;

	if (magic == TARGET_MAGIC) {
		localisation_text->reversed = false;		
	} else if (magic == TARGET_MAGIC_REVERSED) {
		localisation_text->reversed = true;		
	}


}
