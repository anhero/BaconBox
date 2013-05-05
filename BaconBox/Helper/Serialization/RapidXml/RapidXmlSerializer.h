#ifndef BB_RAPID_XML_SERIALIZER_H
#define BB_RAPID_XML_SERIALIZER_H

#include "BaconBox/Helper/Serialization/Serializer.h"

namespace BaconBox {
	class RapidXmlSerializer : public Serializer {
	public:
		/**
		 * Default constructor.
		 */
		RapidXmlSerializer();
		
		/**
		 * Copy constructor.
		 * @param src RapidXmlSerializer to make a copy of.
		 */
		RapidXmlSerializer(const RapidXmlSerializer &src);
		
		/**
		 * Destructor.
		 */
		~RapidXmlSerializer();
		
		/**
		 * Assignment operator overload.
		 * @param src RapidXmlSerializer to copy.
		 * @return Reference to the current instance.
		 */
		RapidXmlSerializer &operator=(const RapidXmlSerializer &src);
		
		/**
		 * Writes the content of the value to a stream.
		 * @param output Output stream to output to.
		 * @param value Value to output in the stream.
		 */
		void writeToStream(std::ostream &output, const Value &value);
		
		/**
		 * Reads the content of a value from a stream.
		 * @param input Input stream to read the value from.
		 * @param value Value to read the data to.
		 * @return True on success, false on error.
		 */
		bool readFromStream(std::istream &input, Value &value);
	private:
	};
}

#endif /* defined(BB_RAPID_XML_SERIALIZER_H) */

