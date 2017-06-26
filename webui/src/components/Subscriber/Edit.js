import { Component } from 'react';
import PropTypes from 'prop-types';

import { Form } from 'components';

const schema = {
  "title": "",
  "type": "object",
  "properties": {
    "imsi": {
      "type": "string", 
      "title": "IMSI (International Mobile Subscriber Identity)",
      "required": true,
      "pattern": "^\\d+$",
      "messages": {
        "required": "is required",
        "pattern": "does not match decimal digit pattern"
      }
    },
    "security": {
      "title": "Security",
      "type": "object",
      "properties": {
        "k": {
          "type": "string",
          "title": "K (UE Key)",
          "default": "465B5CE8B199B49FAA5F0A2EE238A6BC",
          "required": true,
          "pattern": "^[0-9|a-f|A-F]+$",
          "messages": {
            "required": "is required",
            "pattern": "does not match two hexadecimal digit pattern"
          }
        },
        "op": {
          "type": "string",
          "title": "OP (Operator Key)",
          "default": "5F1D289C5D354D0A140C2548F5F3E3BA",
          "required": true,
          "pattern": "^[0-9|a-f|A-F]+$",
          "messages": {
            "required": "is required",
            "pattern": "does not match two hexadecimal digit pattern"
          }
        },
        "amf": {
          "type": "string",
          "title": "AMF (Authentication Management Field)",
          "default": "8000",
          "required": true,
          "pattern": "^[0-9|a-f|A-F]+$",
          "messages": {
            "required": "is required",
            "pattern": "does not match two hexadecimal digit pattern"
          }
        }
      }
    },
    "ue_ambr": {
      "type": "object",
      "title": "UE AMBR - Aggregate Maximum Bit Rate",
      "properties": {
        "max_bandwidth_ul": {
          "type": "number",
          "title": "Max Requested Bandwidth UL (Kbps)",
          "default": 1024000,
          "required": true,
          "messages": {
            "required": "is required",
          }
        },
        "max_bandwidth_dl": {
          "type": "number",
          "title": "Max Requested Bandwidth DL (Kbps)",
          "default": 1024000,
          "required": true,
          "messages": {
            "required": "is required",
          }
        }
      }
    },
    "pdn": {
      "type": "array",
      "title": "PDN - Packet Data Network",
      "minItems": 1,
      "messages": {
        "minItems": "does not meet minimum PDN of 1"
      },
      "items": {
        "type": "object",
        "properties": {
          "apn": {
            "type": "string",
            "title": "APN (Access Point Name)",
            "default": "internet",
            "required": true,
            "messages": {
              "required": "is required",
            }
          },
          "qos": {
            "type": "object",
            "title": "EPS Subscribed QoS Profile",
            "properties": {
              "qci": {
                "type": "number",
                "title": "QCI (QoS Class Identifier)",
                "enum": [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 65, 66, 69, 70 ],
                "default": 9
              },
              "arp" : {
                "type": "object",
                "title": "",
                "properties": {
                  "priority_level": {
                    "type": "number",
                    "title": "ARP Priority Level (1~15)",
                    "default": 8,
                    "minimum": 1,
                    "maximum": 15,
                    "required": true,
                    "messages": {
                      "required": "is required",
                    }
                  }
                }
              }
            }
          },
          "pdn_ambr": {
            "type": "object",
            "title": "APN AMBR - Aggragate Maximum Bit Rate",
            "properties": {
              "max_bandwidth_ul": {
                "type": "number",
                "title": "Max Requested Bandwidth UL (Kbps)",
                "default": 1024000,
                "required": true,
                "messages": {
                  "required": "is required",
                }
              },
              "max_bandwidth_dl": {
                "type": "number",
                "title": "Max Requested Bandwidth DL (Kbps)",
                "default": 1024000,
                "required": true,
                "messages": {
                  "required": "is required",
                }
              }
            }
          }
        }
      }
    }
  }
};

const uiSchema = {
  "imsi": {
    "ui:autofocus": true,
  },
  "pdn": {
    "ui:options":  {
      "orderable": false
    },
    "items": {
      "qos": {
        "qci": {
          "ui:widget": "radio",
          "ui:options": {
            "inline": true
          }
        }
      }
    }
  }
}

class Edit extends Component {
  static propTypes = {
    visible: PropTypes.bool, 
    onHide: PropTypes.func, 
    onSubmit: PropTypes.func,
  }

  render() {
    const {
      visible,
      onHide,
      onSubmit
    } = this.props;

    return (
      <Form 
        schema={schema}
        uiSchema={uiSchema}
        visible={visible}
        title="Create Subscriber"
        onHide={onHide}
        onSubmit={onSubmit}>
      </Form>
    )
  }
}

export default Edit;