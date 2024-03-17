

#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include "parse_request_data.h"


        /**
         * @brief 初始化ParseRequestData对象
         */
        ParseRequestData::ParseRequestData() :
            _requestBuffer(new RequestBuffer),
            _bodySize(0),
            _leaveBodySize(0)
        {
            _requestBuffer->req_status_ = kRequestStateNone;
        }

        /**
         * @brief 解析原始数据
         * @param data 原始数据
         * @param dataSize 数据大小
         */
        bool ParseRequestData::PareseRequestHeader(const char* data,
            const std::size_t& dataSize, std::size_t& dataIndex, std::string& encrypt_key_part)
        {
            MessageHeader msg_header;
            if (dataSize < sizeof(MessageHeader))
            {
                return false;
            }

            ::memcpy(&msg_header, data, sizeof(MessageHeader));
            msg_header.order_num_ = be32toh(msg_header.order_num_);
            msg_header.method_ = be16toh(msg_header.method_);

            _requestBuffer->method_ = msg_header.method_;
            _requestBuffer->order_num_ = msg_header.order_num_;
            _requestBuffer->status_num_ = msg_header.status_num_;
            _requestBuffer->encript_func_ = msg_header.encript_func_;

            encrypt_key_part.clear();
            encrypt_key_part.push_back((char)msg_header.header_length_);
            encrypt_key_part.push_back((char)msg_header.protocol_ver_);

            dataIndex += sizeof(MessageHeader);

            return true;
        }

        bool ParseRequestData::PareseRequestBody(const char* data,
            const std::size_t& dataSize, std::size_t& dataIndex)
        {
            std::string lineData;
            if (_requestBuffer->req_status_ == kRequestStateParam) {
                if (!this->readParamData(data, dataSize, dataIndex, lineData))
                    return false;
            }

            if (_requestBuffer->req_status_ == kRequestStateProp) {
                if (!this->readPropData(data, dataSize, dataIndex, lineData))
                    return false;
            }

            if (_requestBuffer->req_status_ == kRequestStateBody) {
                if (!this->readBodyData(data, dataSize, dataIndex))
                    return false;
            }

            //	if (_requestBuffer->req_status_ == kRequestStateDone) {
            //		if (!this->readDataDone(data, dataSize, dataIndex)) {
            //			_requestBuffer->req_status_ = kRequestStateError;
            //		}
            //
            //		return false;
            //	}

            return (_requestBuffer->req_status_ == kRequestStateDone);
        }

        /**
         * @brief 解析原始数据
         * @param data 原始数据
         * @param dataSize 数据大小
         */
        bool ParseRequestData::parseAllData(const char* data,
            const std::size_t& dataSize)
        {

            std::size_t dataIndex = 0;
            _requestBuffer.reset(new RequestBuffer);

            std::string encrypt_key_part;
            if (!PareseRequestHeader(data, dataSize, dataIndex, encrypt_key_part))
            {
                return false;
            }

            if (dataIndex == dataSize)
            {
                _requestBuffer->req_status_ = kRequestStateDone;
                return true;
            }

            std::string psw_key = encrypt_key_part;
            if (_requestBuffer->encript_func_ != MsgProtocolEncryptFuc::kFuncNone)
            {
                std::string dedata;
                if (MsgProtocolEncryptFuc::kFuncSM4 == _requestBuffer->encript_func_)
                {
                    std::string endata;
                    endata.assign(data + dataIndex, dataSize - dataIndex);

                }
                else if (MsgProtocolEncryptFuc::kFuncAes == _requestBuffer->encript_func_)
                {
                    std::string endata;
                    endata.assign(data + dataIndex, dataSize - dataIndex);
                }
                else
                {
                    _requestBuffer->req_status_ = kRequestStateError;
                    return false;
                }

                std::size_t decode_index = 0;
                _requestBuffer->req_status_ = kRequestStateParam;
                if (!PareseRequestBody(dedata.c_str(), dedata.size(), decode_index))
                {
                    return false;
                }
            }
            else
            {
                _requestBuffer->req_status_ = kRequestStateParam;
                if (!PareseRequestBody(data, dataSize, dataIndex))
                {
                    return false;
                }
            }

            return true;
        }

        /**
         * @brief 解析命令行数据
         * @param data 原始数据
         * @param dataSize 原始数据大小
         * @param dataIndex 数据下标
         * @param lineData 单行数据
         * @return 返回解析数据是否成功
         */
        bool ParseRequestData::readParamData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex,
            std::string& lineData)
        {
            if (this->lineData(data, dataSize, dataIndex, lineData)) {
                if (lineData.length() > 0)
                {
                    if (!this->processLineData(lineData)) {
                        _bufferLine.clear();
                        _requestBuffer->req_status_ = kRequestStateError;
                        return false;
                    }
                    _requestBuffer->req_status_ = kRequestStateProp;
                }
                else
                {
                    if (dataSize > dataIndex)
                    {
                        _requestBuffer->req_status_ = kRequestStateProp;
                    }
                    else
                    {
                        _requestBuffer->req_status_ = kRequestStateDone;
                    }
                }

            }
            else {
                return false;

            }

            return true;
        }

        /**
         * @brief 解析prop数据
         * @param data 原始数据
         * @param dataSize 原始数据大小
         * @param dataIndex 数据下标
         * @param lineData 行数据
         * @return 返回解析数据是否成功
         */
        bool ParseRequestData::readPropData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex,
            std::string& lineData)
        {
            while (this->lineData(data, dataSize, dataIndex, lineData)) {
                if (lineData.length() > 0) {
                    if (!this->processLineData(lineData)) {
                        _bufferLine.clear();
                        _requestBuffer->req_status_ = kRequestStateError;
                        return false;
                    }

                }
                else {
                    _requestBuffer->req_status_ = kRequestStateBody;
                    break;
                }

            }

            if (lineData.length() == 0) {
                _bodySize = GetBodySize();
                if (_bodySize > 0) {
                    _requestBuffer->req_status_ = kRequestStateBody;

                }
                else {
                    _requestBuffer->req_status_ = kRequestStateDone;
                }
            }

            return true;
        }

        /**
         * @brief 解析body数据
         * @param data 原始数据
         * @param dataSize 数据大小
         * @param dataIndex 数据下标
         * @return 返回解析数据是否成功
         */
        bool ParseRequestData::readBodyData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex)
        {
            if (dataIndex + _bodySize > dataSize)
            {
                _requestBuffer->req_status_ = kRequestStateError;
                return false;
            }

            if (dataSize == dataIndex) {
                _requestBuffer->req_status_ = kRequestStateDone;
                return true;
            }

            _requestBuffer->body_.assign(data + dataIndex, _bodySize);
            _requestBuffer->req_status_ = kRequestStateDone;

            return true;
        }

        /**
         * @brief 解析数据完成后的处理
         * @param data 原始数据
         * @param dataSize 数据大小
         * @param dataIndex 数据下标
         * @return 返回处理是否成功
         */
        bool ParseRequestData::readDataDone(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex)
        {
            if (this->propValueToInt("isstrcmd") == 1) {
                const char* tmpData = data;
                if (tmpData[dataIndex] == '\0')
                    ++dataIndex;
            }

            if (dataSize < dataIndex) {
                return false;
            }

            return true;
        }

        /**
         * @brief 解析行数据
         * @param data 原始数据
         * @param dataSize 数据大小
         * @param dataIndex 数据下标
         * @param lineData 行数据
         * @return 返回解析是否成功
         */
        bool ParseRequestData::lineData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex,
            std::string& lineData)
        {
            bool lineEnd = false;
            std::string tmpData;
            tmpData.assign(data, dataSize);
            lineData.clear();
            while (dataIndex < dataSize && !lineEnd) {
                char ch = tmpData.at(dataIndex);
#ifdef PLATFORM_MIPS
                std::cout << "#" << ch << std::endl;   /* 如果将该语句去掉，服务器收到消息就会奔溃 */
#endif

                switch (ch) {
                case '\r':
                    break;
                case '\n':
                    lineEnd = true;
                    break;
                default:
                    _bufferLine.push_back(ch);
                    break;
                }
                ++dataIndex;
            }
            if (lineEnd) {
                lineData.assign(_bufferLine.begin(), _bufferLine.end());
                _bufferLine.clear();
            }

            return lineEnd;
        }

        /**
         * @brief 操作行数据
         * @param lineData 行数据
         * @return 返回操作是否成功
         */
        bool ParseRequestData::processLineData(std::string& lineData)
        {
            std::size_t operateIndex = 0;

            if (_requestBuffer->req_status_ == kRequestStateNone) {
                _requestBuffer->req_status_ = kRequestStateParam;
            }

            if (_requestBuffer->req_status_ == kRequestStateParam) {
                if (!lineData.empty()) {
                    this->setParams(lineData);
                }
            }

            if (_requestBuffer->req_status_ == kRequestStateProp) {
                operateIndex = lineData.find(':');
                if (operateIndex != std::string::npos) {
                    std::string key = lineData.substr(0, operateIndex);
                    std::string value;

                    if (key.empty())
                        return false;

                    value = lineData.substr(operateIndex + 1,
                        lineData.length() - (operateIndex + 1));
                    this->setPropItem(key, value);

                }
                else {
                    return false;

                }
            }

            return true;
        }

        /**
         * @brief 判断是否有body数据
         * @return 返回判断结果
         */
        std::size_t ParseRequestData::GetBodySize()
        {
            std::size_t body_size = 0;
            std::string strValue = this->propValue("content-length");

            if (!strValue.empty()) {
                body_size = std::atoi(strValue.c_str());
            }

            return body_size;
        }

        /**
         * @brief 设置method数据
         * @param method 具体数据
         */
        void ParseRequestData::setMethod(const unsigned short method)
        {
            _requestBuffer->method_ = method;
        }

        /**
         * @brief 设置params数据
         * @param lineDataSubstr 子串数据
         */
        void ParseRequestData::setParams(const std::string& lineDataSubstr)
        {
            //_requestBuffer->params_.clear();

            //std::string paramItem;
            //std::size_t tmpBegin = 0;
            //std::size_t tmpPos = 0;
            //bool isEnd = false;

            //do {
            //    tmpPos = lineDataSubstr.find(' ', tmpBegin);
            //    paramItem.clear();
            //    if (tmpPos != std::string::npos) {
            //        paramItem = lineDataSubstr.substr(tmpBegin, tmpPos - tmpBegin);

            //    }
            //    else {
            //        paramItem = lineDataSubstr.substr(tmpBegin, lineDataSubstr.length() - tmpBegin);
            //        isEnd = true;

            //    }

            //    _requestBuffer->params_.push_back(_utils.decodeURL(paramItem));

            //    if (tmpPos == std::string::npos)
            //        break;
            //    tmpBegin = tmpPos + 1;

            //} while (!isEnd);

        }

        /**
         * @brief 设置prop数据
         * @param key prop的键
         * @param value prop的值
         */
        void ParseRequestData::setPropItem(std::string& key, std::string value)
        {
            if (value.empty())
                return;

            //key = _utils.toLower(key);
            //_utils.trimLeft(value);

            _requestBuffer->props_[key] = value;
        }

        /**
         * @brief 获取prop的某个值
         * @param key prop的键
         * @return 返回prop的某个值
         */
        std::string ParseRequestData::propValue(std::string key)
        {
            PropMap::iterator it = _requestBuffer->props_.find(key);

            if (it != _requestBuffer->props_.end())
                return it->second;

            return std::string();
        }

        /**
         * @brief 获取prop的某个值并转换成int
         * @param key prop的键
         * @return 返回prop的某个值得int数值
         */
        std::size_t ParseRequestData::propValueToInt(std::string key)
        {
            std::string propValue = this->propValue(key);

            return std::atoi(propValue.c_str());
        }

