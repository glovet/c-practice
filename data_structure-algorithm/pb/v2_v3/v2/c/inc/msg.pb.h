// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#ifndef PROTOBUF_msg_2eproto__INCLUDED
#define PROTOBUF_msg_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace proto2_proto {
class Message;
class MessageDefaultTypeInternal;
extern MessageDefaultTypeInternal _Message_default_instance_;
}  // namespace proto2_proto

namespace proto2_proto {

namespace protobuf_msg_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_msg_2eproto

enum Message_Humour {
  Message_Humour_UNKNOWN = 0,
  Message_Humour_PUNS = 1,
  Message_Humour_SLAPSTICK = 2,
  Message_Humour_BILL_BAILEY = 3
};
bool Message_Humour_IsValid(int value);
const Message_Humour Message_Humour_Humour_MIN = Message_Humour_UNKNOWN;
const Message_Humour Message_Humour_Humour_MAX = Message_Humour_BILL_BAILEY;
const int Message_Humour_Humour_ARRAYSIZE = Message_Humour_Humour_MAX + 1;

const ::google::protobuf::EnumDescriptor* Message_Humour_descriptor();
inline const ::std::string& Message_Humour_Name(Message_Humour value) {
  return ::google::protobuf::internal::NameOfEnum(
    Message_Humour_descriptor(), value);
}
inline bool Message_Humour_Parse(
    const ::std::string& name, Message_Humour* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Message_Humour>(
    Message_Humour_descriptor(), name, value);
}
// ===================================================================

class Message : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:proto2_proto.Message) */ {
 public:
  Message();
  virtual ~Message();

  Message(const Message& from);

  inline Message& operator=(const Message& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Message(Message&& from) noexcept
    : Message() {
    *this = ::std::move(from);
  }

  inline Message& operator=(Message&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Message& default_instance();

  static inline const Message* internal_default_instance() {
    return reinterpret_cast<const Message*>(
               &_Message_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Message* other);
  friend void swap(Message& a, Message& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Message* New() const PROTOBUF_FINAL { return New(NULL); }

  Message* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Message& from);
  void MergeFrom(const Message& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Message* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef Message_Humour Humour;
  static const Humour UNKNOWN =
    Message_Humour_UNKNOWN;
  static const Humour PUNS =
    Message_Humour_PUNS;
  static const Humour SLAPSTICK =
    Message_Humour_SLAPSTICK;
  static const Humour BILL_BAILEY =
    Message_Humour_BILL_BAILEY;
  static inline bool Humour_IsValid(int value) {
    return Message_Humour_IsValid(value);
  }
  static const Humour Humour_MIN =
    Message_Humour_Humour_MIN;
  static const Humour Humour_MAX =
    Message_Humour_Humour_MAX;
  static const int Humour_ARRAYSIZE =
    Message_Humour_Humour_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Humour_descriptor() {
    return Message_Humour_descriptor();
  }
  static inline const ::std::string& Humour_Name(Humour value) {
    return Message_Humour_Name(value);
  }
  static inline bool Humour_Parse(const ::std::string& name,
      Humour* value) {
    return Message_Humour_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated uint64 key = 5 [packed = true];
  int key_size() const;
  void clear_key();
  static const int kKeyFieldNumber = 5;
  ::google::protobuf::uint64 key(int index) const;
  void set_key(int index, ::google::protobuf::uint64 value);
  void add_key(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      key() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_key();

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional bytes data = 4;
  bool has_data() const;
  void clear_data();
  static const int kDataFieldNumber = 4;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  #if LANG_CXX11
  void set_data(::std::string&& value);
  #endif
  void set_data(const char* value);
  void set_data(const void* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // optional .proto2_proto.Message.Humour hilarity = 2;
  bool has_hilarity() const;
  void clear_hilarity();
  static const int kHilarityFieldNumber = 2;
  ::proto2_proto::Message_Humour hilarity() const;
  void set_hilarity(::proto2_proto::Message_Humour value);

  // optional uint32 height_in_cm = 3;
  bool has_height_in_cm() const;
  void clear_height_in_cm();
  static const int kHeightInCmFieldNumber = 3;
  ::google::protobuf::uint32 height_in_cm() const;
  void set_height_in_cm(::google::protobuf::uint32 value);

  // optional int64 result_count = 7;
  bool has_result_count() const;
  void clear_result_count();
  static const int kResultCountFieldNumber = 7;
  ::google::protobuf::int64 result_count() const;
  void set_result_count(::google::protobuf::int64 value);

  // optional bool true_scotsman = 8;
  bool has_true_scotsman() const;
  void clear_true_scotsman();
  static const int kTrueScotsmanFieldNumber = 8;
  bool true_scotsman() const;
  void set_true_scotsman(bool value);

  // optional float score = 9;
  bool has_score() const;
  void clear_score();
  static const int kScoreFieldNumber = 9;
  float score() const;
  void set_score(float value);

  // @@protoc_insertion_point(class_scope:proto2_proto.Message)
 private:
  void set_has_name();
  void clear_has_name();
  void set_has_hilarity();
  void clear_has_hilarity();
  void set_has_height_in_cm();
  void clear_has_height_in_cm();
  void set_has_data();
  void clear_has_data();
  void set_has_result_count();
  void clear_has_result_count();
  void set_has_true_scotsman();
  void clear_has_true_scotsman();
  void set_has_score();
  void clear_has_score();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > key_;
  mutable int _key_cached_byte_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  int hilarity_;
  ::google::protobuf::uint32 height_in_cm_;
  ::google::protobuf::int64 result_count_;
  bool true_scotsman_;
  float score_;
  friend struct protobuf_msg_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Message

// optional string name = 1;
inline bool Message::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& Message::name() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.name)
  return name_.GetNoArena();
}
inline void Message::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:proto2_proto.Message.name)
}
#if LANG_CXX11
inline void Message::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:proto2_proto.Message.name)
}
#endif
inline void Message::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:proto2_proto.Message.name)
}
inline void Message::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:proto2_proto.Message.name)
}
inline ::std::string* Message::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:proto2_proto.Message.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Message::release_name() {
  // @@protoc_insertion_point(field_release:proto2_proto.Message.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Message::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:proto2_proto.Message.name)
}

// optional .proto2_proto.Message.Humour hilarity = 2;
inline bool Message::has_hilarity() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Message::set_has_hilarity() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Message::clear_has_hilarity() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Message::clear_hilarity() {
  hilarity_ = 0;
  clear_has_hilarity();
}
inline ::proto2_proto::Message_Humour Message::hilarity() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.hilarity)
  return static_cast< ::proto2_proto::Message_Humour >(hilarity_);
}
inline void Message::set_hilarity(::proto2_proto::Message_Humour value) {
  assert(::proto2_proto::Message_Humour_IsValid(value));
  set_has_hilarity();
  hilarity_ = value;
  // @@protoc_insertion_point(field_set:proto2_proto.Message.hilarity)
}

// optional uint32 height_in_cm = 3;
inline bool Message::has_height_in_cm() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Message::set_has_height_in_cm() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Message::clear_has_height_in_cm() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Message::clear_height_in_cm() {
  height_in_cm_ = 0u;
  clear_has_height_in_cm();
}
inline ::google::protobuf::uint32 Message::height_in_cm() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.height_in_cm)
  return height_in_cm_;
}
inline void Message::set_height_in_cm(::google::protobuf::uint32 value) {
  set_has_height_in_cm();
  height_in_cm_ = value;
  // @@protoc_insertion_point(field_set:proto2_proto.Message.height_in_cm)
}

// optional bytes data = 4;
inline bool Message::has_data() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message::set_has_data() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message::clear_has_data() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
inline const ::std::string& Message::data() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.data)
  return data_.GetNoArena();
}
inline void Message::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:proto2_proto.Message.data)
}
#if LANG_CXX11
inline void Message::set_data(::std::string&& value) {
  set_has_data();
  data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:proto2_proto.Message.data)
}
#endif
inline void Message::set_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:proto2_proto.Message.data)
}
inline void Message::set_data(const void* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:proto2_proto.Message.data)
}
inline ::std::string* Message::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:proto2_proto.Message.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Message::release_data() {
  // @@protoc_insertion_point(field_release:proto2_proto.Message.data)
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Message::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:proto2_proto.Message.data)
}

// optional int64 result_count = 7;
inline bool Message::has_result_count() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Message::set_has_result_count() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Message::clear_has_result_count() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Message::clear_result_count() {
  result_count_ = GOOGLE_LONGLONG(0);
  clear_has_result_count();
}
inline ::google::protobuf::int64 Message::result_count() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.result_count)
  return result_count_;
}
inline void Message::set_result_count(::google::protobuf::int64 value) {
  set_has_result_count();
  result_count_ = value;
  // @@protoc_insertion_point(field_set:proto2_proto.Message.result_count)
}

// optional bool true_scotsman = 8;
inline bool Message::has_true_scotsman() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Message::set_has_true_scotsman() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Message::clear_has_true_scotsman() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Message::clear_true_scotsman() {
  true_scotsman_ = false;
  clear_has_true_scotsman();
}
inline bool Message::true_scotsman() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.true_scotsman)
  return true_scotsman_;
}
inline void Message::set_true_scotsman(bool value) {
  set_has_true_scotsman();
  true_scotsman_ = value;
  // @@protoc_insertion_point(field_set:proto2_proto.Message.true_scotsman)
}

// optional float score = 9;
inline bool Message::has_score() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void Message::set_has_score() {
  _has_bits_[0] |= 0x00000040u;
}
inline void Message::clear_has_score() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void Message::clear_score() {
  score_ = 0;
  clear_has_score();
}
inline float Message::score() const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.score)
  return score_;
}
inline void Message::set_score(float value) {
  set_has_score();
  score_ = value;
  // @@protoc_insertion_point(field_set:proto2_proto.Message.score)
}

// repeated uint64 key = 5 [packed = true];
inline int Message::key_size() const {
  return key_.size();
}
inline void Message::clear_key() {
  key_.Clear();
}
inline ::google::protobuf::uint64 Message::key(int index) const {
  // @@protoc_insertion_point(field_get:proto2_proto.Message.key)
  return key_.Get(index);
}
inline void Message::set_key(int index, ::google::protobuf::uint64 value) {
  key_.Set(index, value);
  // @@protoc_insertion_point(field_set:proto2_proto.Message.key)
}
inline void Message::add_key(::google::protobuf::uint64 value) {
  key_.Add(value);
  // @@protoc_insertion_point(field_add:proto2_proto.Message.key)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
Message::key() const {
  // @@protoc_insertion_point(field_list:proto2_proto.Message.key)
  return key_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
Message::mutable_key() {
  // @@protoc_insertion_point(field_mutable_list:proto2_proto.Message.key)
  return &key_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace proto2_proto

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::proto2_proto::Message_Humour> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::proto2_proto::Message_Humour>() {
  return ::proto2_proto::Message_Humour_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_msg_2eproto__INCLUDED
