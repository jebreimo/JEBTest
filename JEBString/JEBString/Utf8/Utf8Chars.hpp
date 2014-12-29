#ifndef JEBSTRING_UTF8_UTF8CHARS_HPP
#define JEBSTRING_UTF8_UTF8CHARS_HPP

#include "JEBString/JEBStringDefinitions.hpp"

#define UTF8_NULL                                "\x00"
#define UTF8_START_OF_HEADING                    "\x01"
#define UTF8_START_OF_TEXT                       "\x02"
#define UTF8_END_OF_TEXT                         "\x03"
#define UTF8_END_OF_TRANSMISSION                 "\x04"
#define UTF8_ENQUIRY                             "\x05"
#define UTF8_ACKNOWLEDGE                         "\x06"
#define UTF8_BELL                                "\x07"
#define UTF8_BACKSPACE                           "\x08"
#define UTF8_CHARACTER_TABULATION                "\x09"
#define UTF8_LINE_FEED                           "\x0A"
#define UTF8_LINE_TABULATION                     "\x0B"
#define UTF8_FORM_FEED                           "\x0C"
#define UTF8_CARRIAGE_RETURN                     "\x0D"
#define UTF8_SHIFT_OUT                           "\x0E"
#define UTF8_SHIFT_IN                            "\x0F"
#define UTF8_DATA_LINK_ESCAPE                    "\x10"
#define UTF8_DEVICE_CONTROL_ONE                  "\x11"
#define UTF8_DEVICE_CONTROL_TWO                  "\x12"
#define UTF8_DEVICE_CONTROL_THREE                "\x13"
#define UTF8_DEVICE_CONTROL_FOUR                 "\x14"
#define UTF8_NEGATIVE_ACKNOWLEDGE                "\x15"
#define UTF8_SYNCHRONOUS_IDLE                    "\x16"
#define UTF8_END_OF_TRANSMISSION_BLOCK           "\x17"
#define UTF8_CANCEL                              "\x18"
#define UTF8_END_OF_MEDIUM                       "\x19"
#define UTF8_SUBSTITUTE                          "\x1A"
#define UTF8_ESCAPE                              "\x1B"
#define UTF8_INFORMATION_SEPARATOR_FOUR          "\x1C"
#define UTF8_INFORMATION_SEPARATOR_THREE         "\x1D"
#define UTF8_INFORMATION_SEPARATOR_TWO           "\x1E"
#define UTF8_INFORMATION_SEPARATOR_ONE           "\x1F"
#define UTF8_DELETE                              "\x7F"
#define UTF8_BREAK_PERMITTED_HERE                "\xC2\x82"
#define UTF8_NO_BREAK_HERE                       "\xC2\x83"
#define UTF8_NEXT_LINE                           "\xC2\x85"
#define UTF8_START_OF_SELECTED_AREA              "\xC2\x86"
#define UTF8_END_OF_SELECTED_AREA                "\xC2\x87"
#define UTF8_CHARACTER_TABULATION_SET            "\xC2\x88"
#define UTF8_CHARACTER_TABULATION_WITH_JUSTIFICATION "\xC2\x89"
#define UTF8_LINE_TABULATION_SET                 "\xC2\x8A"
#define UTF8_PARTIAL_LINE_FORWARD                "\xC2\x8B"
#define UTF8_PARTIAL_LINE_BACKWARD               "\xC2\x8C"
#define UTF8_REVERSE_LINE_FEED                   "\xC2\x8D"
#define UTF8_SINGLE_SHIFT_TWO                    "\xC2\x8E"
#define UTF8_SINGLE_SHIFT_THREE                  "\xC2\x8F"
#define UTF8_DEVICE_CONTROL_STRING               "\xC2\x90"
#define UTF8_PRIVATE_USE_ONE                     "\xC2\x91"
#define UTF8_PRIVATE_USE_TWO                     "\xC2\x92"
#define UTF8_SET_TRANSMIT_STATE                  "\xC2\x93"
#define UTF8_CANCEL_CHARACTER                    "\xC2\x94"
#define UTF8_MESSAGE_WAITING                     "\xC2\x95"
#define UTF8_START_OF_GUARDED_AREA               "\xC2\x96"
#define UTF8_END_OF_GUARDED_AREA                 "\xC2\x97"
#define UTF8_START_OF_STRING                     "\xC2\x98"
#define UTF8_SINGLE_CHARACTER_INTRODUCER         "\xC2\x9A"
#define UTF8_CONTROL_SEQUENCE_INTRODUCER         "\xC2\x9B"
#define UTF8_STRING_TERMINATOR                   "\xC2\x9C"
#define UTF8_OPERATING_SYSTEM_COMMAND            "\xC2\x9D"
#define UTF8_PRIVACY_MESSAGE                     "\xC2\x9E"
#define UTF8_APPLICATION_PROGRAM_COMMAND         "\xC2\x9F"
#define UTF8_NO_BREAK_SPACE                      "\xC2\xA0"
#define UTF8_INVERTED_EXCLAMATION_MARK           "\xC2\xA1"
#define UTF8_CENT_SIGN                           "\xC2\xA2"
#define UTF8_POUND_SIGN                          "\xC2\xA3"
#define UTF8_CURRENCY_SIGN                       "\xC2\xA4"
#define UTF8_YEN_SIGN                            "\xC2\xA5"
#define UTF8_BROKEN_BAR                          "\xC2\xA6"
#define UTF8_SECTION_SIGN                        "\xC2\xA7"
#define UTF8_DIAERESIS                           "\xC2\xA8"
#define UTF8_COPYRIGHT_SIGN                      "\xC2\xA9"
#define UTF8_FEMININE_ORDINAL_INDICATOR          "\xC2\xAA"
#define UTF8_LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK "\xC2\xAB"
#define UTF8_NOT_SIGN                            "\xC2\xAC"
#define UTF8_SOFT_HYPHEN                         "\xC2\xAD"
#define UTF8_REGISTERED_SIGN                     "\xC2\xAE"
#define UTF8_MACRON                              "\xC2\xAF"
#define UTF8_DEGREE_SIGN                         "\xC2\xB0"
#define UTF8_PLUS_MINUS_SIGN                     "\xC2\xB1"
#define UTF8_SUPERSCRIPT_TWO                     "\xC2\xB2"
#define UTF8_SUPERSCRIPT_THREE                   "\xC2\xB3"
#define UTF8_ACUTE_ACCENT                        "\xC2\xB4"
#define UTF8_MICRO_SIGN                          "\xC2\xB5"
#define UTF8_PILCROW_SIGN                        "\xC2\xB6"
#define UTF8_MIDDLE_DOT                          "\xC2\xB7"
#define UTF8_CEDILLA                             "\xC2\xB8"
#define UTF8_SUPERSCRIPT_ONE                     "\xC2\xB9"
#define UTF8_MASCULINE_ORDINAL_INDICATOR         "\xC2\xBA"
#define UTF8_RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK "\xC2\xBB"
#define UTF8_VULGAR_FRACTION_ONE_QUARTER         "\xC2\xBC"
#define UTF8_VULGAR_FRACTION_ONE_HALF            "\xC2\xBD"
#define UTF8_VULGAR_FRACTION_THREE_QUARTERS      "\xC2\xBE"
#define UTF8_INVERTED_QUESTION_MARK              "\xC2\xBF"
#define UTF8_LATIN_CAPITAL_A_WITH_GRAVE          "\xC3\x80"
#define UTF8_LATIN_CAPITAL_A_WITH_ACUTE          "\xC3\x81"
#define UTF8_LATIN_CAPITAL_A_WITH_CIRCUMFLEX     "\xC3\x82"
#define UTF8_LATIN_CAPITAL_A_WITH_TILDE          "\xC3\x83"
#define UTF8_LATIN_CAPITAL_A_WITH_DIAERESIS      "\xC3\x84"
#define UTF8_LATIN_CAPITAL_A_WITH_RING_ABOVE     "\xC3\x85"
#define UTF8_LATIN_CAPITAL_AE                    "\xC3\x86"
#define UTF8_LATIN_CAPITAL_C_WITH_CEDILLA        "\xC3\x87"
#define UTF8_LATIN_CAPITAL_E_WITH_GRAVE          "\xC3\x88"
#define UTF8_LATIN_CAPITAL_E_WITH_ACUTE          "\xC3\x89"
#define UTF8_LATIN_CAPITAL_E_WITH_CIRCUMFLEX     "\xC3\x8A"
#define UTF8_LATIN_CAPITAL_E_WITH_DIAERESIS      "\xC3\x8B"
#define UTF8_LATIN_CAPITAL_I_WITH_GRAVE          "\xC3\x8C"
#define UTF8_LATIN_CAPITAL_I_WITH_ACUTE          "\xC3\x8D"
#define UTF8_LATIN_CAPITAL_I_WITH_CIRCUMFLEX     "\xC3\x8E"
#define UTF8_LATIN_CAPITAL_I_WITH_DIAERESIS      "\xC3\x8F"
#define UTF8_LATIN_CAPITAL_ETH                   "\xC3\x90"
#define UTF8_LATIN_CAPITAL_N_WITH_TILDE          "\xC3\x91"
#define UTF8_LATIN_CAPITAL_O_WITH_GRAVE          "\xC3\x92"
#define UTF8_LATIN_CAPITAL_O_WITH_ACUTE          "\xC3\x93"
#define UTF8_LATIN_CAPITAL_O_WITH_CIRCUMFLEX     "\xC3\x94"
#define UTF8_LATIN_CAPITAL_O_WITH_TILDE          "\xC3\x95"
#define UTF8_LATIN_CAPITAL_O_WITH_DIAERESIS      "\xC3\x96"
#define UTF8_MULTIPLICATION_SIGN                 "\xC3\x97"
#define UTF8_LATIN_CAPITAL_O_WITH_STROKE         "\xC3\x98"
#define UTF8_LATIN_CAPITAL_U_WITH_GRAVE          "\xC3\x99"
#define UTF8_LATIN_CAPITAL_U_WITH_ACUTE          "\xC3\x9A"
#define UTF8_LATIN_CAPITAL_U_WITH_CIRCUMFLEX     "\xC3\x9B"
#define UTF8_LATIN_CAPITAL_U_WITH_DIAERESIS      "\xC3\x9C"
#define UTF8_LATIN_CAPITAL_Y_WITH_ACUTE          "\xC3\x9D"
#define UTF8_LATIN_CAPITAL_THORN                 "\xC3\x9E"
#define UTF8_LATIN_SMALL_SHARP_S                 "\xC3\x9F"
#define UTF8_LATIN_SMALL_A_WITH_GRAVE            "\xC3\xA0"
#define UTF8_LATIN_SMALL_A_WITH_ACUTE            "\xC3\xA1"
#define UTF8_LATIN_SMALL_A_WITH_CIRCUMFLEX       "\xC3\xA2"
#define UTF8_LATIN_SMALL_A_WITH_TILDE            "\xC3\xA3"
#define UTF8_LATIN_SMALL_A_WITH_DIAERESIS        "\xC3\xA4"
#define UTF8_LATIN_SMALL_A_WITH_RING_ABOVE       "\xC3\xA5"
#define UTF8_LATIN_SMALL_AE                      "\xC3\xA6"
#define UTF8_LATIN_SMALL_C_WITH_CEDILLA          "\xC3\xA7"
#define UTF8_LATIN_SMALL_E_WITH_GRAVE            "\xC3\xA8"
#define UTF8_LATIN_SMALL_E_WITH_ACUTE            "\xC3\xA9"
#define UTF8_LATIN_SMALL_E_WITH_CIRCUMFLEX       "\xC3\xAA"
#define UTF8_LATIN_SMALL_E_WITH_DIAERESIS        "\xC3\xAB"
#define UTF8_LATIN_SMALL_I_WITH_GRAVE            "\xC3\xAC"
#define UTF8_LATIN_SMALL_I_WITH_ACUTE            "\xC3\xAD"
#define UTF8_LATIN_SMALL_I_WITH_CIRCUMFLEX       "\xC3\xAE"
#define UTF8_LATIN_SMALL_I_WITH_DIAERESIS        "\xC3\xAF"
#define UTF8_LATIN_SMALL_ETH                     "\xC3\xB0"
#define UTF8_LATIN_SMALL_N_WITH_TILDE            "\xC3\xB1"
#define UTF8_LATIN_SMALL_O_WITH_GRAVE            "\xC3\xB2"
#define UTF8_LATIN_SMALL_O_WITH_ACUTE            "\xC3\xB3"
#define UTF8_LATIN_SMALL_O_WITH_CIRCUMFLEX       "\xC3\xB4"
#define UTF8_LATIN_SMALL_O_WITH_TILDE            "\xC3\xB5"
#define UTF8_LATIN_SMALL_O_WITH_DIAERESIS        "\xC3\xB6"
#define UTF8_DIVISION_SIGN                       "\xC3\xB7"
#define UTF8_LATIN_SMALL_O_WITH_STROKE           "\xC3\xB8"
#define UTF8_LATIN_SMALL_U_WITH_GRAVE            "\xC3\xB9"
#define UTF8_LATIN_SMALL_U_WITH_ACUTE            "\xC3\xBA"
#define UTF8_LATIN_SMALL_U_WITH_CIRCUMFLEX       "\xC3\xBB"
#define UTF8_LATIN_SMALL_U_WITH_DIAERESIS        "\xC3\xBC"
#define UTF8_LATIN_SMALL_Y_WITH_ACUTE            "\xC3\xBD"
#define UTF8_LATIN_SMALL_THORN                   "\xC3\xBE"
#define UTF8_LATIN_SMALL_Y_WITH_DIAERESIS        "\xC3\xBF"
#define UTF8_COMBINING_GRAVE_ACCENT              "\xCC\x80"
#define UTF8_COMBINING_ACUTE_ACCENT              "\xCC\x81"
#define UTF8_COMBINING_CIRCUMFLEX_ACCENT         "\xCC\x82"
#define UTF8_COMBINING_TILDE                     "\xCC\x83"
#define UTF8_COMBINING_MACRON                    "\xCC\x84"
#define UTF8_COMBINING_OVERLINE                  "\xCC\x85"
#define UTF8_COMBINING_BREVE                     "\xCC\x86"
#define UTF8_COMBINING_DOT_ABOVE                 "\xCC\x87"
#define UTF8_COMBINING_DIAERESIS                 "\xCC\x88"
#define UTF8_COMBINING_HOOK_ABOVE                "\xCC\x89"
#define UTF8_COMBINING_RING_ABOVE                "\xCC\x8A"
#define UTF8_COMBINING_DOUBLE_ACUTE_ACCENT       "\xCC\x8B"
#define UTF8_COMBINING_CARON                     "\xCC\x8C"
#define UTF8_COMBINING_VERTICAL_LINE_ABOVE       "\xCC\x8D"
#define UTF8_COMBINING_DOUBLE_VERTICAL_LINE_ABOVE "\xCC\x8E"
#define UTF8_COMBINING_DOUBLE_GRAVE_ACCENT       "\xCC\x8F"
#define UTF8_COMBINING_CANDRABINDU               "\xCC\x90"
#define UTF8_COMBINING_INVERTED_BREVE            "\xCC\x91"
#define UTF8_COMBINING_TURNED_COMMA_ABOVE        "\xCC\x92"
#define UTF8_COMBINING_COMMA_ABOVE               "\xCC\x93"
#define UTF8_COMBINING_REVERSED_COMMA_ABOVE      "\xCC\x94"
#define UTF8_COMBINING_COMMA_ABOVE_RIGHT         "\xCC\x95"
#define UTF8_COMBINING_GRAVE_ACCENT_BELOW        "\xCC\x96"
#define UTF8_COMBINING_ACUTE_ACCENT_BELOW        "\xCC\x97"
#define UTF8_COMBINING_LEFT_TACK_BELOW           "\xCC\x98"
#define UTF8_COMBINING_RIGHT_TACK_BELOW          "\xCC\x99"
#define UTF8_COMBINING_LEFT_ANGLE_ABOVE          "\xCC\x9A"
#define UTF8_COMBINING_HORN                      "\xCC\x9B"
#define UTF8_COMBINING_LEFT_HALF_RING_BELOW      "\xCC\x9C"
#define UTF8_COMBINING_UP_TACK_BELOW             "\xCC\x9D"
#define UTF8_COMBINING_DOWN_TACK_BELOW           "\xCC\x9E"
#define UTF8_COMBINING_PLUS_SIGN_BELOW           "\xCC\x9F"
#define UTF8_COMBINING_MINUS_SIGN_BELOW          "\xCC\xA0"
#define UTF8_COMBINING_PALATALIZED_HOOK_BELOW    "\xCC\xA1"
#define UTF8_COMBINING_RETROFLEX_HOOK_BELOW      "\xCC\xA2"
#define UTF8_COMBINING_DOT_BELOW                 "\xCC\xA3"
#define UTF8_COMBINING_DIAERESIS_BELOW           "\xCC\xA4"
#define UTF8_COMBINING_RING_BELOW                "\xCC\xA5"
#define UTF8_COMBINING_COMMA_BELOW               "\xCC\xA6"
#define UTF8_COMBINING_CEDILLA                   "\xCC\xA7"
#define UTF8_COMBINING_OGONEK                    "\xCC\xA8"
#define UTF8_COMBINING_VERTICAL_LINE_BELOW       "\xCC\xA9"
#define UTF8_COMBINING_BRIDGE_BELOW              "\xCC\xAA"
#define UTF8_COMBINING_INVERTED_DOUBLE_ARCH_BELOW "\xCC\xAB"
#define UTF8_COMBINING_CARON_BELOW               "\xCC\xAC"
#define UTF8_COMBINING_CIRCUMFLEX_ACCENT_BELOW   "\xCC\xAD"
#define UTF8_COMBINING_BREVE_BELOW               "\xCC\xAE"
#define UTF8_COMBINING_INVERTED_BREVE_BELOW      "\xCC\xAF"
#define UTF8_COMBINING_TILDE_BELOW               "\xCC\xB0"
#define UTF8_COMBINING_MACRON_BELOW              "\xCC\xB1"
#define UTF8_COMBINING_LOW_LINE                  "\xCC\xB2"
#define UTF8_COMBINING_DOUBLE_LOW_LINE           "\xCC\xB3"
#define UTF8_COMBINING_TILDE_OVERLAY             "\xCC\xB4"
#define UTF8_COMBINING_SHORT_STROKE_OVERLAY      "\xCC\xB5"
#define UTF8_COMBINING_LONG_STROKE_OVERLAY       "\xCC\xB6"
#define UTF8_COMBINING_SHORT_SOLIDUS_OVERLAY     "\xCC\xB7"
#define UTF8_COMBINING_LONG_SOLIDUS_OVERLAY      "\xCC\xB8"
#define UTF8_COMBINING_RIGHT_HALF_RING_BELOW     "\xCC\xB9"
#define UTF8_COMBINING_INVERTED_BRIDGE_BELOW     "\xCC\xBA"
#define UTF8_COMBINING_SQUARE_BELOW              "\xCC\xBB"
#define UTF8_COMBINING_SEAGULL_BELOW             "\xCC\xBC"
#define UTF8_COMBINING_X_ABOVE                   "\xCC\xBD"
#define UTF8_COMBINING_VERTICAL_TILDE            "\xCC\xBE"
#define UTF8_COMBINING_DOUBLE_OVERLINE           "\xCC\xBF"
#define UTF8_COMBINING_GRAVE_TONE_MARK           "\xCD\x80"
#define UTF8_COMBINING_ACUTE_TONE_MARK           "\xCD\x81"
#define UTF8_COMBINING_GREEK_PERISPOMENI         "\xCD\x82"
#define UTF8_COMBINING_GREEK_KORONIS             "\xCD\x83"
#define UTF8_COMBINING_GREEK_DIALYTIKA_TONOS     "\xCD\x84"
#define UTF8_COMBINING_GREEK_YPOGEGRAMMENI       "\xCD\x85"
#define UTF8_COMBINING_BRIDGE_ABOVE              "\xCD\x86"
#define UTF8_COMBINING_EQUALS_SIGN_BELOW         "\xCD\x87"
#define UTF8_COMBINING_DOUBLE_VERTICAL_LINE_BELOW "\xCD\x88"
#define UTF8_COMBINING_LEFT_ANGLE_BELOW          "\xCD\x89"
#define UTF8_COMBINING_NOT_TILDE_ABOVE           "\xCD\x8A"
#define UTF8_COMBINING_HOMOTHETIC_ABOVE          "\xCD\x8B"
#define UTF8_COMBINING_ALMOST_EQUAL_TO_ABOVE     "\xCD\x8C"
#define UTF8_COMBINING_LEFT_RIGHT_ARROW_BELOW    "\xCD\x8D"
#define UTF8_COMBINING_UPWARDS_ARROW_BELOW       "\xCD\x8E"
#define UTF8_COMBINING_GRAPHEME_JOINER           "\xCD\x8F"
#define UTF8_COMBINING_RIGHT_ARROWHEAD_ABOVE     "\xCD\x90"
#define UTF8_COMBINING_LEFT_HALF_RING_ABOVE      "\xCD\x91"
#define UTF8_COMBINING_FERMATA                   "\xCD\x92"
#define UTF8_COMBINING_X_BELOW                   "\xCD\x93"
#define UTF8_COMBINING_LEFT_ARROWHEAD_BELOW      "\xCD\x94"
#define UTF8_COMBINING_RIGHT_ARROWHEAD_BELOW     "\xCD\x95"
#define UTF8_COMBINING_RIGHT_ARROWHEAD_AND_UP_ARROWHEAD_BELOW "\xCD\x96"
#define UTF8_COMBINING_RIGHT_HALF_RING_ABOVE     "\xCD\x97"
#define UTF8_COMBINING_DOT_ABOVE_RIGHT           "\xCD\x98"
#define UTF8_COMBINING_ASTERISK_BELOW            "\xCD\x99"
#define UTF8_COMBINING_DOUBLE_RING_BELOW         "\xCD\x9A"
#define UTF8_COMBINING_ZIGZAG_ABOVE              "\xCD\x9B"
#define UTF8_COMBINING_DOUBLE_BREVE_BELOW        "\xCD\x9C"
#define UTF8_COMBINING_DOUBLE_BREVE              "\xCD\x9D"
#define UTF8_COMBINING_DOUBLE_MACRON             "\xCD\x9E"
#define UTF8_COMBINING_DOUBLE_MACRON_BELOW       "\xCD\x9F"
#define UTF8_COMBINING_DOUBLE_TILDE              "\xCD\xA0"
#define UTF8_COMBINING_DOUBLE_INVERTED_BREVE     "\xCD\xA1"
#define UTF8_COMBINING_DOUBLE_RIGHTWARDS_ARROW_BELOW "\xCD\xA2"
#define UTF8_COMBINING_LATIN_SMALL_A             "\xCD\xA3"
#define UTF8_COMBINING_LATIN_SMALL_E             "\xCD\xA4"
#define UTF8_COMBINING_LATIN_SMALL_I             "\xCD\xA5"
#define UTF8_COMBINING_LATIN_SMALL_O             "\xCD\xA6"
#define UTF8_COMBINING_LATIN_SMALL_U             "\xCD\xA7"
#define UTF8_COMBINING_LATIN_SMALL_C             "\xCD\xA8"
#define UTF8_COMBINING_LATIN_SMALL_D             "\xCD\xA9"
#define UTF8_COMBINING_LATIN_SMALL_H             "\xCD\xAA"
#define UTF8_COMBINING_LATIN_SMALL_M             "\xCD\xAB"
#define UTF8_COMBINING_LATIN_SMALL_R             "\xCD\xAC"
#define UTF8_COMBINING_LATIN_SMALL_T             "\xCD\xAD"
#define UTF8_COMBINING_LATIN_SMALL_V             "\xCD\xAE"
#define UTF8_COMBINING_LATIN_SMALL_X             "\xCD\xAF"
#define UTF8_GREEK_CAPITAL_ALPHA                 "\xCE\x91"
#define UTF8_GREEK_CAPITAL_BETA                  "\xCE\x92"
#define UTF8_GREEK_CAPITAL_GAMMA                 "\xCE\x93"
#define UTF8_GREEK_CAPITAL_DELTA                 "\xCE\x94"
#define UTF8_GREEK_CAPITAL_EPSILON               "\xCE\x95"
#define UTF8_GREEK_CAPITAL_ZETA                  "\xCE\x96"
#define UTF8_GREEK_CAPITAL_ETA                   "\xCE\x97"
#define UTF8_GREEK_CAPITAL_THETA                 "\xCE\x98"
#define UTF8_GREEK_CAPITAL_IOTA                  "\xCE\x99"
#define UTF8_GREEK_CAPITAL_KAPPA                 "\xCE\x9A"
#define UTF8_GREEK_CAPITAL_LAMDA                 "\xCE\x9B"
#define UTF8_GREEK_CAPITAL_MU                    "\xCE\x9C"
#define UTF8_GREEK_CAPITAL_NU                    "\xCE\x9D"
#define UTF8_GREEK_CAPITAL_XI                    "\xCE\x9E"
#define UTF8_GREEK_CAPITAL_OMICRON               "\xCE\x9F"
#define UTF8_GREEK_CAPITAL_PI                    "\xCE\xA0"
#define UTF8_GREEK_CAPITAL_RHO                   "\xCE\xA1"
#define UTF8_GREEK_CAPITAL_SIGMA                 "\xCE\xA3"
#define UTF8_GREEK_CAPITAL_TAU                   "\xCE\xA4"
#define UTF8_GREEK_CAPITAL_UPSILON               "\xCE\xA5"
#define UTF8_GREEK_CAPITAL_PHI                   "\xCE\xA6"
#define UTF8_GREEK_CAPITAL_CHI                   "\xCE\xA7"
#define UTF8_GREEK_CAPITAL_PSI                   "\xCE\xA8"
#define UTF8_GREEK_CAPITAL_OMEGA                 "\xCE\xA9"
#define UTF8_GREEK_SMALL_ALPHA                   "\xCE\xB1"
#define UTF8_GREEK_SMALL_BETA                    "\xCE\xB2"
#define UTF8_GREEK_SMALL_GAMMA                   "\xCE\xB3"
#define UTF8_GREEK_SMALL_DELTA                   "\xCE\xB4"
#define UTF8_GREEK_SMALL_EPSILON                 "\xCE\xB5"
#define UTF8_GREEK_SMALL_ZETA                    "\xCE\xB6"
#define UTF8_GREEK_SMALL_ETA                     "\xCE\xB7"
#define UTF8_GREEK_SMALL_THETA                   "\xCE\xB8"
#define UTF8_GREEK_SMALL_IOTA                    "\xCE\xB9"
#define UTF8_GREEK_SMALL_KAPPA                   "\xCE\xBA"
#define UTF8_GREEK_SMALL_LAMDA                   "\xCE\xBB"
#define UTF8_GREEK_SMALL_MU                      "\xCE\xBC"
#define UTF8_GREEK_SMALL_NU                      "\xCE\xBD"
#define UTF8_GREEK_SMALL_XI                      "\xCE\xBE"
#define UTF8_GREEK_SMALL_OMICRON                 "\xCE\xBF"
#define UTF8_GREEK_SMALL_PI                      "\xCF\x80"
#define UTF8_GREEK_SMALL_RHO                     "\xCF\x81"
#define UTF8_GREEK_SMALL_FINAL_SIGMA             "\xCF\x82"
#define UTF8_GREEK_SMALL_SIGMA                   "\xCF\x83"
#define UTF8_GREEK_SMALL_TAU                     "\xCF\x84"
#define UTF8_GREEK_SMALL_UPSILON                 "\xCF\x85"
#define UTF8_GREEK_SMALL_PHI                     "\xCF\x86"
#define UTF8_GREEK_SMALL_CHI                     "\xCF\x87"
#define UTF8_GREEK_SMALL_PSI                     "\xCF\x88"
#define UTF8_GREEK_SMALL_OMEGA                   "\xCF\x89"
#define UTF8_OGHAM_SPACE_MARK                    "\xE1\x9A\x80"
#define UTF8_MONGOLIAN_VOWEL_SEPARATOR           "\xE1\xA0\x8E"
#define UTF8_EN_QUAD                             "\xE2\x80\x80"
#define UTF8_EM_QUAD                             "\xE2\x80\x81"
#define UTF8_EN_SPACE                            "\xE2\x80\x82"
#define UTF8_EM_SPACE                            "\xE2\x80\x83"
#define UTF8_THREE_PER_EM_SPACE                  "\xE2\x80\x84"
#define UTF8_FOUR_PER_EM_SPACE                   "\xE2\x80\x85"
#define UTF8_SIX_PER_EM_SPACE                    "\xE2\x80\x86"
#define UTF8_FIGURE_SPACE                        "\xE2\x80\x87"
#define UTF8_PUNCTUATION_SPACE                   "\xE2\x80\x88"
#define UTF8_THIN_SPACE                          "\xE2\x80\x89"
#define UTF8_HAIR_SPACE                          "\xE2\x80\x8A"
#define UTF8_ZERO_WIDTH_SPACE                    "\xE2\x80\x8B"
#define UTF8_ZERO_WIDTH_NON_JOINER               "\xE2\x80\x8C"
#define UTF8_ZERO_WIDTH_JOINER                   "\xE2\x80\x8D"
#define UTF8_LINE_SEPARATOR                      "\xE2\x80\xA8"
#define UTF8_PARAGRAPH_SEPARATOR                 "\xE2\x80\xA9"
#define UTF8_NARROW_NO_BREAK_SPACE               "\xE2\x80\xAF"
#define UTF8_MEDIUM_MATHEMATICAL_SPACE           "\xE2\x81\x9F"
#define UTF8_WORD_JOINER                         "\xE2\x81\xA0"
#define UTF8_IDEOGRAPHIC_SPACE                   "\xE3\x80\x80"
#define UTF8_ZERO_WIDTH_NO_BREAK_SPACE           "\xEF\xBB\xBF"

#endif
