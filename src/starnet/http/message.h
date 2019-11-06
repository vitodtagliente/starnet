#pragma once

#include "../internet/message.h"

namespace starnet
{
	namespace http
	{
		class Message : public internet::Message
		{
		public:

			enum class Version
			{
				v1,
				v2
			};

			enum class Connection
			{
				Close,
				KeepAlive
			};

			Message() : internet::Message() {}
			Message(const std::string& source);
			Message(const Message& message) : internet::Message(message) {}

			virtual std::string toString() const override;

			void setVersion(const Version version) { m_version = version; }
			Version getVersione() const { return m_version; }

			void setConnection(const Connection connection);
			Connection getConnection() const;

		protected:

			Version m_version;

		};
	}
}