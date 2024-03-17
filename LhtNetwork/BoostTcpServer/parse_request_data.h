
#ifndef _INC_BIGANTSERVER_ANTNETIO_PARSE_REQUEST_DATA_H
#define _INC_BIGANTSERVER_ANTNETIO_PARSE_REQUEST_DATA_H

#include <vector>
#include "message_protocol.h"


        /**
         * @brief 解析请求数据类
         */
        class ParseRequestData
        {
        public:
            explicit ParseRequestData();

            bool parseAllData(const char* data,
                const std::size_t& dataSize);

        public:
            RequestBufferPtr _requestBuffer;    /**< 请求数据的缓冲区 */

        private:
            bool readParamData(const char* data,
                const std::size_t& dataSize,
                std::size_t& dataIndex,
                std::string& lineData);
            bool readPropData(const char* data,
                const std::size_t& dataSize,
                std::size_t& dataIndex,
                std::string& lineData);
            bool readBodyData(const char* data,
                const std::size_t& dataSize,
                std::size_t& dataIndex);
            bool readDataDone(const char* data,
                const std::size_t& dataSize,
                std::size_t& dataIndex);

            bool lineData(const char* data,
                const std::size_t& dataSize,
                std::size_t& dataIndex,
                std::string& line);
            bool processLineData(std::string& lineData);
            std::size_t GetBodySize();

            void setMethod(const unsigned short method);
            void setParams(const std::string& lineDataSubstr);
            void setPropItem(std::string& key, std::string value);

            std::string propValue(std::string key);
            std::size_t propValueToInt(std::string key);

            bool PareseRequestHeader(const char* data,
                const std::size_t& dataSize, std::size_t& dataIndex, std::string& encrypt_key_part);

            bool PareseRequestBody(const char* data,
                const std::size_t& dataSize, std::size_t& dataIndex);

        private:

            std::size_t _bodySize;          /**< body数据的大小 */
            std::size_t _leaveBodySize;     /**< 剩余body数据的大小 */
            std::vector<char> _bufferLine;  /**< 行缓冲数据 */

        };

#endif // _INC_BIGANTSERVER_ANTNETIO_PARSE_REQUEST_DATA_H
