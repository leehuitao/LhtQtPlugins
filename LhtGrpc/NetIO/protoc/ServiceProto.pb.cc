// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServiceProto.proto

#include "ServiceProto.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = ::PROTOBUF_NAMESPACE_ID::internal;
namespace ServiceNetIO {
PROTOBUF_CONSTEXPR NewMessageRequest::NewMessageRequest(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.header_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.server_name_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.encode_type_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.body_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.order_id_)*/ ::int64_t{0}

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct NewMessageRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR NewMessageRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~NewMessageRequestDefaultTypeInternal() {}
  union {
    NewMessageRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 NewMessageRequestDefaultTypeInternal _NewMessageRequest_default_instance_;
PROTOBUF_CONSTEXPR ServiceMessageResponse::ServiceMessageResponse(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.send_user_name_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.send_user_id_)*/ ::int64_t{0}

  , /*decltype(_impl_.send_order_id_)*/ ::int64_t{0}

  , /*decltype(_impl_.send_status_)*/ 0

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ServiceMessageResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ServiceMessageResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ServiceMessageResponseDefaultTypeInternal() {}
  union {
    ServiceMessageResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ServiceMessageResponseDefaultTypeInternal _ServiceMessageResponse_default_instance_;
}  // namespace ServiceNetIO
static ::_pb::Metadata file_level_metadata_ServiceProto_2eproto[2];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_ServiceProto_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_ServiceProto_2eproto = nullptr;
const ::uint32_t TableStruct_ServiceProto_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::NewMessageRequest, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::NewMessageRequest, _impl_.header_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::NewMessageRequest, _impl_.server_name_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::NewMessageRequest, _impl_.order_id_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::NewMessageRequest, _impl_.encode_type_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::NewMessageRequest, _impl_.body_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::ServiceMessageResponse, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::ServiceMessageResponse, _impl_.send_status_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::ServiceMessageResponse, _impl_.send_user_id_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::ServiceMessageResponse, _impl_.send_user_name_),
    PROTOBUF_FIELD_OFFSET(::ServiceNetIO::ServiceMessageResponse, _impl_.send_order_id_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, -1, -1, sizeof(::ServiceNetIO::NewMessageRequest)},
        { 13, -1, -1, sizeof(::ServiceNetIO::ServiceMessageResponse)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::ServiceNetIO::_NewMessageRequest_default_instance_._instance,
    &::ServiceNetIO::_ServiceMessageResponse_default_instance_._instance,
};
const char descriptor_table_protodef_ServiceProto_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\022ServiceProto.proto\022\014ServiceNetIO\"m\n\021Ne"
    "wMessageRequest\022\016\n\006header\030\001 \001(\014\022\023\n\013serve"
    "r_name\030\002 \001(\t\022\020\n\010order_id\030\003 \001(\003\022\023\n\013encode"
    "_type\030\004 \001(\t\022\014\n\004body\030\005 \001(\014\"r\n\026ServiceMess"
    "ageResponse\022\023\n\013send_status\030\001 \001(\005\022\024\n\014send"
    "_user_id\030\002 \001(\003\022\026\n\016send_user_name\030\003 \001(\t\022\025"
    "\n\rsend_order_id\030\004 \001(\0032n\n\024UserServiceInte"
    "rface\022V\n\tNewNotify\022\037.ServiceNetIO.NewMes"
    "sageRequest\032$.ServiceNetIO.ServiceMessag"
    "eResponse(\0010\001B\021Z\017./;ServiceNetIOb\006proto3"
};
static ::absl::once_flag descriptor_table_ServiceProto_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_ServiceProto_2eproto = {
    false,
    false,
    400,
    descriptor_table_protodef_ServiceProto_2eproto,
    "ServiceProto.proto",
    &descriptor_table_ServiceProto_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_ServiceProto_2eproto::offsets,
    file_level_metadata_ServiceProto_2eproto,
    file_level_enum_descriptors_ServiceProto_2eproto,
    file_level_service_descriptors_ServiceProto_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_ServiceProto_2eproto_getter() {
  return &descriptor_table_ServiceProto_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_ServiceProto_2eproto(&descriptor_table_ServiceProto_2eproto);
namespace ServiceNetIO {
// ===================================================================

class NewMessageRequest::_Internal {
 public:
};

NewMessageRequest::NewMessageRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServiceNetIO.NewMessageRequest)
}
NewMessageRequest::NewMessageRequest(const NewMessageRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  NewMessageRequest* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.header_) {}

    , decltype(_impl_.server_name_) {}

    , decltype(_impl_.encode_type_) {}

    , decltype(_impl_.body_) {}

    , decltype(_impl_.order_id_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.header_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.header_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_header().empty()) {
    _this->_impl_.header_.Set(from._internal_header(), _this->GetArenaForAllocation());
  }
  _impl_.server_name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.server_name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_server_name().empty()) {
    _this->_impl_.server_name_.Set(from._internal_server_name(), _this->GetArenaForAllocation());
  }
  _impl_.encode_type_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.encode_type_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_encode_type().empty()) {
    _this->_impl_.encode_type_.Set(from._internal_encode_type(), _this->GetArenaForAllocation());
  }
  _impl_.body_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.body_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_body().empty()) {
    _this->_impl_.body_.Set(from._internal_body(), _this->GetArenaForAllocation());
  }
  _this->_impl_.order_id_ = from._impl_.order_id_;
  // @@protoc_insertion_point(copy_constructor:ServiceNetIO.NewMessageRequest)
}

inline void NewMessageRequest::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.header_) {}

    , decltype(_impl_.server_name_) {}

    , decltype(_impl_.encode_type_) {}

    , decltype(_impl_.body_) {}

    , decltype(_impl_.order_id_) { ::int64_t{0} }

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.header_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.header_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.server_name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.server_name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.encode_type_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.encode_type_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.body_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.body_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

NewMessageRequest::~NewMessageRequest() {
  // @@protoc_insertion_point(destructor:ServiceNetIO.NewMessageRequest)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void NewMessageRequest::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.header_.Destroy();
  _impl_.server_name_.Destroy();
  _impl_.encode_type_.Destroy();
  _impl_.body_.Destroy();
}

void NewMessageRequest::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void NewMessageRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:ServiceNetIO.NewMessageRequest)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.header_.ClearToEmpty();
  _impl_.server_name_.ClearToEmpty();
  _impl_.encode_type_.ClearToEmpty();
  _impl_.body_.ClearToEmpty();
  _impl_.order_id_ = ::int64_t{0};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* NewMessageRequest::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bytes header = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_header();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // string server_name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_server_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ServiceNetIO.NewMessageRequest.server_name"));
        } else {
          goto handle_unusual;
        }
        continue;
      // int64 order_id = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 24)) {
          _impl_.order_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // string encode_type = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_encode_type();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ServiceNetIO.NewMessageRequest.encode_type"));
        } else {
          goto handle_unusual;
        }
        continue;
      // bytes body = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_body();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* NewMessageRequest::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServiceNetIO.NewMessageRequest)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes header = 1;
  if (!this->_internal_header().empty()) {
    const std::string& _s = this->_internal_header();
    target = stream->WriteBytesMaybeAliased(1, _s, target);
  }

  // string server_name = 2;
  if (!this->_internal_server_name().empty()) {
    const std::string& _s = this->_internal_server_name();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServiceNetIO.NewMessageRequest.server_name");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  // int64 order_id = 3;
  if (this->_internal_order_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(
        3, this->_internal_order_id(), target);
  }

  // string encode_type = 4;
  if (!this->_internal_encode_type().empty()) {
    const std::string& _s = this->_internal_encode_type();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServiceNetIO.NewMessageRequest.encode_type");
    target = stream->WriteStringMaybeAliased(4, _s, target);
  }

  // bytes body = 5;
  if (!this->_internal_body().empty()) {
    const std::string& _s = this->_internal_body();
    target = stream->WriteBytesMaybeAliased(5, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServiceNetIO.NewMessageRequest)
  return target;
}

::size_t NewMessageRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServiceNetIO.NewMessageRequest)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes header = 1;
  if (!this->_internal_header().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
                                    this->_internal_header());
  }

  // string server_name = 2;
  if (!this->_internal_server_name().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_server_name());
  }

  // string encode_type = 4;
  if (!this->_internal_encode_type().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_encode_type());
  }

  // bytes body = 5;
  if (!this->_internal_body().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
                                    this->_internal_body());
  }

  // int64 order_id = 3;
  if (this->_internal_order_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_order_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData NewMessageRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    NewMessageRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*NewMessageRequest::GetClassData() const { return &_class_data_; }


void NewMessageRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<NewMessageRequest*>(&to_msg);
  auto& from = static_cast<const NewMessageRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServiceNetIO.NewMessageRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_header().empty()) {
    _this->_internal_set_header(from._internal_header());
  }
  if (!from._internal_server_name().empty()) {
    _this->_internal_set_server_name(from._internal_server_name());
  }
  if (!from._internal_encode_type().empty()) {
    _this->_internal_set_encode_type(from._internal_encode_type());
  }
  if (!from._internal_body().empty()) {
    _this->_internal_set_body(from._internal_body());
  }
  if (from._internal_order_id() != 0) {
    _this->_internal_set_order_id(from._internal_order_id());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void NewMessageRequest::CopyFrom(const NewMessageRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServiceNetIO.NewMessageRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NewMessageRequest::IsInitialized() const {
  return true;
}

void NewMessageRequest::InternalSwap(NewMessageRequest* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.header_, lhs_arena,
                                       &other->_impl_.header_, rhs_arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.server_name_, lhs_arena,
                                       &other->_impl_.server_name_, rhs_arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.encode_type_, lhs_arena,
                                       &other->_impl_.encode_type_, rhs_arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.body_, lhs_arena,
                                       &other->_impl_.body_, rhs_arena);

  swap(_impl_.order_id_, other->_impl_.order_id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata NewMessageRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ServiceProto_2eproto_getter, &descriptor_table_ServiceProto_2eproto_once,
      file_level_metadata_ServiceProto_2eproto[0]);
}
// ===================================================================

class ServiceMessageResponse::_Internal {
 public:
};

ServiceMessageResponse::ServiceMessageResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServiceNetIO.ServiceMessageResponse)
}
ServiceMessageResponse::ServiceMessageResponse(const ServiceMessageResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  ServiceMessageResponse* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.send_user_name_) {}

    , decltype(_impl_.send_user_id_) {}

    , decltype(_impl_.send_order_id_) {}

    , decltype(_impl_.send_status_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.send_user_name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.send_user_name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_send_user_name().empty()) {
    _this->_impl_.send_user_name_.Set(from._internal_send_user_name(), _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.send_user_id_, &from._impl_.send_user_id_,
    static_cast<::size_t>(reinterpret_cast<char*>(&_impl_.send_status_) -
    reinterpret_cast<char*>(&_impl_.send_user_id_)) + sizeof(_impl_.send_status_));
  // @@protoc_insertion_point(copy_constructor:ServiceNetIO.ServiceMessageResponse)
}

inline void ServiceMessageResponse::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.send_user_name_) {}

    , decltype(_impl_.send_user_id_) { ::int64_t{0} }

    , decltype(_impl_.send_order_id_) { ::int64_t{0} }

    , decltype(_impl_.send_status_) { 0 }

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.send_user_name_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.send_user_name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

ServiceMessageResponse::~ServiceMessageResponse() {
  // @@protoc_insertion_point(destructor:ServiceNetIO.ServiceMessageResponse)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ServiceMessageResponse::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.send_user_name_.Destroy();
}

void ServiceMessageResponse::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void ServiceMessageResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:ServiceNetIO.ServiceMessageResponse)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.send_user_name_.ClearToEmpty();
  ::memset(&_impl_.send_user_id_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.send_status_) -
      reinterpret_cast<char*>(&_impl_.send_user_id_)) + sizeof(_impl_.send_status_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ServiceMessageResponse::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 send_status = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 8)) {
          _impl_.send_status_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // int64 send_user_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 16)) {
          _impl_.send_user_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // string send_user_name = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_send_user_name();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ServiceNetIO.ServiceMessageResponse.send_user_name"));
        } else {
          goto handle_unusual;
        }
        continue;
      // int64 send_order_id = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 32)) {
          _impl_.send_order_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* ServiceMessageResponse::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServiceNetIO.ServiceMessageResponse)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 send_status = 1;
  if (this->_internal_send_status() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(
        1, this->_internal_send_status(), target);
  }

  // int64 send_user_id = 2;
  if (this->_internal_send_user_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(
        2, this->_internal_send_user_id(), target);
  }

  // string send_user_name = 3;
  if (!this->_internal_send_user_name().empty()) {
    const std::string& _s = this->_internal_send_user_name();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServiceNetIO.ServiceMessageResponse.send_user_name");
    target = stream->WriteStringMaybeAliased(3, _s, target);
  }

  // int64 send_order_id = 4;
  if (this->_internal_send_order_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(
        4, this->_internal_send_order_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServiceNetIO.ServiceMessageResponse)
  return target;
}

::size_t ServiceMessageResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServiceNetIO.ServiceMessageResponse)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string send_user_name = 3;
  if (!this->_internal_send_user_name().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_send_user_name());
  }

  // int64 send_user_id = 2;
  if (this->_internal_send_user_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_send_user_id());
  }

  // int64 send_order_id = 4;
  if (this->_internal_send_order_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_send_order_id());
  }

  // int32 send_status = 1;
  if (this->_internal_send_status() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_send_status());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ServiceMessageResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    ServiceMessageResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ServiceMessageResponse::GetClassData() const { return &_class_data_; }


void ServiceMessageResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<ServiceMessageResponse*>(&to_msg);
  auto& from = static_cast<const ServiceMessageResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServiceNetIO.ServiceMessageResponse)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_send_user_name().empty()) {
    _this->_internal_set_send_user_name(from._internal_send_user_name());
  }
  if (from._internal_send_user_id() != 0) {
    _this->_internal_set_send_user_id(from._internal_send_user_id());
  }
  if (from._internal_send_order_id() != 0) {
    _this->_internal_set_send_order_id(from._internal_send_order_id());
  }
  if (from._internal_send_status() != 0) {
    _this->_internal_set_send_status(from._internal_send_status());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ServiceMessageResponse::CopyFrom(const ServiceMessageResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServiceNetIO.ServiceMessageResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ServiceMessageResponse::IsInitialized() const {
  return true;
}

void ServiceMessageResponse::InternalSwap(ServiceMessageResponse* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.send_user_name_, lhs_arena,
                                       &other->_impl_.send_user_name_, rhs_arena);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(ServiceMessageResponse, _impl_.send_status_)
      + sizeof(ServiceMessageResponse::_impl_.send_status_)
      - PROTOBUF_FIELD_OFFSET(ServiceMessageResponse, _impl_.send_user_id_)>(
          reinterpret_cast<char*>(&_impl_.send_user_id_),
          reinterpret_cast<char*>(&other->_impl_.send_user_id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata ServiceMessageResponse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ServiceProto_2eproto_getter, &descriptor_table_ServiceProto_2eproto_once,
      file_level_metadata_ServiceProto_2eproto[1]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace ServiceNetIO
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ServiceNetIO::NewMessageRequest*
Arena::CreateMaybeMessage< ::ServiceNetIO::NewMessageRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServiceNetIO::NewMessageRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::ServiceNetIO::ServiceMessageResponse*
Arena::CreateMaybeMessage< ::ServiceNetIO::ServiceMessageResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServiceNetIO::ServiceMessageResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"