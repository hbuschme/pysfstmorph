/* ===========================================================================
 * Diplomarbeit - pysfstmorph.cpp
 * Copyright (C) 2008 Hendrik Buschmeier
 * ======================================================================== */

#include <sstream>

#include "fst.h"
#include "Python.h"

const int GENERATE_MODE = 1;
const int ANALYSE_MODE  = 2;

Transducer *transducer;
char *temp_filename = "None";

/*
 * Use the transducer (either in generate- or in analyse-mode) to rewrite the 
 * input string (GENERATE_MODE, ANALYSE_MODE). This function is not directly 
 * callable from Python.
 * Because of peculiarities in the implementation of SFST it is not possible
 * to access the output of the analyse_string/generate_string directly. As a
 * workaround the result is written into a file and afterwards read out.
 */
const char *transduce(char input[], int mode){
	FILE *temp_file;
 		
 	// Analyse or generate transducer output and write to file
 	temp_file = fopen(temp_filename, "w");
	if (mode == ANALYSE_MODE) {
 		transducer->analyze_string(input, temp_file, true);
	} else if (mode == GENERATE_MODE) {
		transducer->generate_string(input, temp_file, true);
	}
 	fclose(temp_file);
 		
 	// Read transducer output from file
 	char c;
 	std::ostringstream oss(std::ostringstream::out);
 	temp_file = fopen(temp_filename, "r");
 	c = fgetc(temp_file);
 	while (c != EOF) {
 		oss.put(c);
 		c = fgetc(temp_file);
 	}
 	fclose(temp_file);

	return oss.str().c_str();
}

/*
 * Instantiates the SFST transducer class and sets the filename for the
 * temporary file.
 * args: string: transducer_filename
 *       string: temp_filename
 */
extern "C" PyObject *init_transducer(PyObject *self, PyObject *args) {
	char *transducer_filename = "None";
	if (!PyArg_ParseTuple(args, "ss", &transducer_filename, &temp_filename)) {
		return NULL;
	}
	
	// Initialize transducer.
	FILE *transducer_file;
	transducer_file = fopen(transducer_filename, "rb");
	transducer = new Transducer(transducer_file);
	fclose(transducer_file);
	
	return Py_BuildValue("");
}

/*
 * Destroys the transducer object.
 * args: None
 */
extern "C" PyObject *delete_transducer(PyObject *self, PyObject *args) {
	delete transducer;
	return Py_BuildValue("");
}

/*
 * Passes the input to the transducer to analyse it.
 * args: string: input for analysis
 */
extern "C" PyObject *analyse(PyObject *self, PyObject *args) {
	char *analysis_input = "None";
	if (!PyArg_ParseTuple(args, "s", &analysis_input)) {
		return NULL;
	}
	
	const char *result = transduce(analysis_input, ANALYSE_MODE);
	
	return Py_BuildValue("s", result);
}

/*
 * Passes the input to the transducer to generate the word forms.
 * args: string: input for generation
 */
extern "C" PyObject *generate(PyObject *self, PyObject *args) {
	char *generation_input = "None";
	if (!PyArg_ParseTuple(args, "s", &generation_input)) {
		return NULL;
	}
	
	const char *result = transduce(generation_input, GENERATE_MODE);
	
	return Py_BuildValue("s", result);
}

/* --- Python-extension specific code  ------------------------------------ */

/*
 * Structure specifying which methods are visible in the Python module.
 */
static PyMethodDef _pysfstmorph_methods[] = {
	{"init_transducer", init_transducer, METH_VARARGS},
	{"delete_transducer", delete_transducer, METH_VARARGS},
	{"analyse", analyse, METH_VARARGS},
	{"generate", generate, METH_VARARGS},
	{NULL, NULL, 0}
};

/*
 * Special method to initialize this Python extension.
 */
extern "C" void init_pysfstmorph() {
	Py_InitModule("_pysfstmorph", _pysfstmorph_methods);
}