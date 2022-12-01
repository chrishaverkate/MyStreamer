#include <iostream>
#include <string>

#include <gst/gst.h>
#include <stdio.h>

using std::string;

int main(int argc, char* argv[]) {
	GstElement* pipeline;
	GstElement* source;
	GstElement* sink;
	GstBus* bus;
	GstMessage* msg;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	gst_init(&argc, &argv);

	/* Create the elements */
	source = gst_element_factory_make("videotestsrc", "source");
	sink = gst_element_factory_make("autovideosink", "sink");

	// Adding a couple more elements from the "Exercise" step of tutorial 2
	auto filter = gst_element_factory_make("vertigotv", "filter");
	auto converter = gst_element_factory_make("videoconvert", "converter");

	/* Create the empty pipeline */
	pipeline = gst_pipeline_new("test-pipeline");

	if (!pipeline || !source || !sink) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	/* Build the pipeline */
	gst_bin_add_many(GST_BIN(pipeline), source, filter, converter, sink, NULL);

	if (gst_element_link(source, filter) != TRUE) {
		g_printerr("Failed to link source to filter!\n");
		gst_object_unref(pipeline);
		return -1;
	}

	if (gst_element_link(filter, converter) != TRUE) {
		g_printerr("Failed to link filter converter!\n");
		gst_object_unref(pipeline);
		return -1;
	}

	if (gst_element_link(converter, sink) != TRUE) {
		g_printerr("Failed to link converter to sink\n");
		gst_object_unref(pipeline);
		return -1;
	}

	/* Modify the source's properties */
	g_object_set(source, "pattern", 0, NULL);

	// Adding this so the video only runs for 100 frames, then gets an end of stream
	g_object_set(source, "num-buffers", 200, NULL);

	/* Start playing */
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(pipeline);
		return -1;
	}

	/* Wait until error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

	/* Parse message */
	if (msg != NULL) {
		GError* err;
		gchar* debug_info;

		switch (GST_MESSAGE_TYPE(msg)) {
		case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg, &err, &debug_info);
			g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
			g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
			g_clear_error(&err);
			g_free(debug_info);
			break;
		case GST_MESSAGE_EOS:
			g_print("End-Of-Stream reached.\n");
			break;
		default:
			/* We should not reach here because we only asked for ERRORs and EOS */
			g_printerr("Unexpected message received.\n");
			break;
		}

		gst_message_unref(msg);
	}

	/* Free resources */
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
	return 0;
}
//
//int main(int argc, char** argv) {
//	GstElement* pipeline;
//	GstBus* bus;
//	GstMessage* msg;
//
//	/* Initialize GStreamer */
//	gst_init(&argc, &argv);
//
//	/* Build the pipeline */
//	string playbin = "playbin";
//	string camerabin = "camerabin";
//
//	string sintel_trailer = playbin + " uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm";
//	string camera = camerabin + " uri=file:///dev/video2";
//
//	pipeline = gst_parse_launch(camera.c_str(), NULL);
//
//	/* Start playing */
//	gst_element_set_state(pipeline, GST_STATE_PLAYING);
//
//	/* Wait until error or EOS */
//	bus = gst_element_get_bus(pipeline);
//	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
//
//	/* See next tutorial for proper error message handling/parsing */
//	if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
//		g_error("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
//		        "variable set for more details.");
//	}
//
//	/* Free resources */
//	gst_message_unref(msg);
//	gst_object_unref(bus);
//	gst_element_set_state(pipeline, GST_STATE_NULL);
//	gst_object_unref(pipeline);
//	return 0;
//}
