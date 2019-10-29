#pragma once

#include <cstdint>

namespace starnet
{
	namespace http
	{
		enum class StatusCodeCategory : uint8_t
		{
			Informational = 1,
			Success = 2,
			Redirection = 3,
			ClientError = 4,
			ServerError = 5
		};

		enum class StatusCode : unsigned int
		{
			Continue = 100,
			SwitchingProtocols = 101,
			Ok = 200,
			Created = 201,
			Accepted = 202,
			NonAuthoritativeInformation = 203,
			NoContent = 204,
			ResetContent = 205,
			MultipleChoices = 300,
			MovedPermanently = 301,
			Found = 302,
			SeeOther = 303,
			NotModified = 304,
			UseProxy = 305,
			TemporaryRedirect = 307,
			BadRequest = 400,
			Unauthorized = 401,
			PaymentRequired = 402,
			Forbidden = 403,
			NotFound = 404,
			MethodNotAllowed = 405,
			NotAcceptable = 406,
			RequestTimeout = 408,
			Conflict = 409,
			Gone = 410,
			LengthRequired = 411,
			PreconditionFailed = 412,
			PayloadTooLarge = 413,
			UriTooLong = 414,
			UnsupportedMediaType = 415,
			ExpectationFailed = 417,
			UpgradeRequired = 426,
			InternalServerError = 500,
			NotImplemented = 501,
			BadGateway = 502,
			ServiceUnavailable = 503,
			GatewayTimeout = 504,
			HttpVersionNotSupported = 505
		};
	}
}