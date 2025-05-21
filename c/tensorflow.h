const char* TF_Version(void);


typedef struct TF_Graph TF_Graph;
typedef struct TF_Status TF_Status;
typedef struct TF_SessionOptions TF_SessionOptions;
typedef struct TF_Session TF_Session;
typedef struct TF_Buffer {
    void* data;
    size_t length;
    void (*data_deallocator)(void* data, size_t length);
  } TF_Buffer;
  typedef struct TF_Tensor TF_Tensor;
typedef struct TF_Operation TF_Operation;
typedef enum {
    TF_FLOAT = 1,
    TF_DOUBLE = 2,
    TF_INT32 = 3,
    TF_UINT8 = 4,
    TF_INT16 = 5,
    TF_INT8 = 6,
    TF_STRING = 7,
    TF_COMPLEX64 = 8,
    TF_INT64 = 9,
    TF_BOOL = 10,
    TF_QINT8 = 11,
    TF_QUINT8 = 12,
    TF_QINT32 = 13,
    TF_BFLOAT16 = 14,
    TF_QINT16 = 15,
    TF_QUINT16 = 16,
    TF_UINT16 = 17,
    TF_COMPLEX128 = 18,
    TF_HALF = 19,
    TF_RESOURCE = 20,
    TF_VARIANT = 21,
    TF_UINT32 = 22,
    TF_UINT64 = 23
} TF_DataType;

typedef struct {
  TF_Operation* oper;
  int index;
} TF_Output;
typedef void (*TF_Deallocator)(void* data, size_t len, void* arg);


TF_Graph* TF_NewGraph(void);
void TF_DeleteGraph(TF_Graph*);
TF_Operation* TF_GraphOperationByName(const TF_Graph* graph, const char* oper_name);


TF_Status* TF_NewStatus(void);
void TF_DeleteStatus(TF_Status*);

TF_SessionOptions* TF_NewSessionOptions(void);
void TF_DeleteSessionOptions(TF_SessionOptions*);

TF_Session* TF_NewSession(TF_Graph*, const TF_SessionOptions*, TF_Status*);
void TF_CloseSession(TF_Session*, TF_Status*);
void TF_DeleteSession(TF_Session*, TF_Status*);

TF_Buffer* TF_NewBuffer(void);
TF_Buffer* TF_NewBufferFromString(const void* proto, size_t proto_len);
void TF_DeleteBuffer(TF_Buffer*);

void TF_SessionRun(
    TF_Session* session,
    const void* run_options,
    const char* const* input_names,
    TF_Tensor* const* inputs,
    int ninputs,
    const char* const* output_names,
    TF_Tensor** outputs,
    int noutputs,
    const char* const* target_oper_names,
    int ntargets,
    TF_Status* status);

TF_Tensor* TF_AllocateTensor(int data_type, const int64_t* dims, int num_dims, size_t len);
void TF_DeleteTensor(TF_Tensor*);
void* TF_TensorData(const TF_Tensor*);
size_t TF_TensorByteSize(const TF_Tensor*);

int TF_GraphImportGraphDef(TF_Graph*, const TF_Buffer*, const void* options, TF_Status*);

int TF_GetCode(const TF_Status*);
const char* TF_Message(const TF_Status*);
TF_Session* TF_LoadSessionFromSavedModel(
    const TF_SessionOptions* session_options,
    const void* run_options,
    const char* export_dir,
    const char* const* tags,
    int tags_len,
    TF_Graph* graph,
    void* meta_graph_def,
    TF_Status* status);

    TF_Tensor* TF_NewTensor(
        TF_DataType,
        const int64_t* dims,
        int num_dims,
        void* data,
        size_t len,
        TF_Deallocator deallocator,
        void* deallocator_arg);
      