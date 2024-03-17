

#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include "parse_request_data.h"


        /**
         * @brief ��ʼ��ParseRequestData����
         */
        ParseRequestData::ParseRequestData() :
            _requestBuffer(new RequestBuffer),
            _bodySize(0),
            _leaveBodySize(0)
        {
            _requestBuffer->req_status_ = kRequestStateNone;
        }

        /**
         * @brief ����ԭʼ����
         * @param data ԭʼ����
         * @param dataSize ���ݴ�С
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
         * @brief ����ԭʼ����
         * @param data ԭʼ����
         * @param dataSize ���ݴ�С
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
         * @brief ��������������
         * @param data ԭʼ����
         * @param dataSize ԭʼ���ݴ�С
         * @param dataIndex �����±�
         * @param lineData ��������
         * @return ���ؽ��������Ƿ�ɹ�
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
         * @brief ����prop����
         * @param data ԭʼ����
         * @param dataSize ԭʼ���ݴ�С
         * @param dataIndex �����±�
         * @param lineData ������
         * @return ���ؽ��������Ƿ�ɹ�
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
         * @brief ����body����
         * @param data ԭʼ����
         * @param dataSize ���ݴ�С
         * @param dataIndex �����±�
         * @return ���ؽ��������Ƿ�ɹ�
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
         * @brief ����������ɺ�Ĵ���
         * @param data ԭʼ����
         * @param dataSize ���ݴ�С
         * @param dataIndex �����±�
         * @return ���ش����Ƿ�ɹ�
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
         * @brief ����������
         * @param data ԭʼ����
         * @param dataSize ���ݴ�С
         * @param dataIndex �����±�
         * @param lineData ������
         * @return ���ؽ����Ƿ�ɹ�
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
                std::cout << "#" << ch << std::endl;   /* ����������ȥ�����������յ���Ϣ�ͻᱼ�� */
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
         * @brief ����������
         * @param lineData ������
         * @return ���ز����Ƿ�ɹ�
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
         * @brief �ж��Ƿ���body����
         * @return �����жϽ��
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
         * @brief ����method����
         * @param method ��������
         */
        void ParseRequestData::setMethod(const unsigned short method)
        {
            _requestBuffer->method_ = method;
        }

        /**
         * @brief ����params����
         * @param lineDataSubstr �Ӵ�����
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
         * @brief ����prop����
         * @param key prop�ļ�
         * @param value prop��ֵ
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
         * @brief ��ȡprop��ĳ��ֵ
         * @param key prop�ļ�
         * @return ����prop��ĳ��ֵ
         */
        std::string ParseRequestData::propValue(std::string key)
        {
            PropMap::iterator it = _requestBuffer->props_.find(key);

            if (it != _requestBuffer->props_.end())
                return it->second;

            return std::string();
        }

        /**
         * @brief ��ȡprop��ĳ��ֵ��ת����int
         * @param key prop�ļ�
         * @return ����prop��ĳ��ֵ��int��ֵ
         */
        std::size_t ParseRequestData::propValueToInt(std::string key)
        {
            std::string propValue = this->propValue(key);

            return std::atoi(propValue.c_str());
        }

