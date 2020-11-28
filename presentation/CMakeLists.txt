set(SHOWCASE_MAIN_DOC poco_showcase.adoc)

set(SHOWCASE_SOURCES
        ${SHOWCASE}
        api.adoc
        features.adoc
        intro.adoc
        logging.adoc
        poco_showcase.adoc
        uses.adoc
        )

set(HTML_SHOWCASE poco_showcase.html)

message(CHECK_START "Finding AsciiDoc + RevealJS HTML converter")

find_program(HTML_CONVERTER
        NAMES asciidoctor-revealjs
        DOC "AsciiDoc + RevealJS HTML converter")

if(HTML_CONVERTER)
    message(CHECK_PASS "found ${HTML_CONVERTER}")

    add_custom_command(OUTPUT ${HTML_SHOWCASE}
            COMMAND ${HTML_CONVERTER} -a revealjsdir=https://cdn.jsdelivr.net/npm/reveal.js@3.9.2
                                      -r asciidoctor-diagram
                                      -o ${HTML_SHOWCASE}
                                      "${CMAKE_CURRENT_SOURCE_DIR}/${SHOWCASE_MAIN_DOC}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating HTML presentation"
            DEPENDS ${SHOWCASE_SOURCES}
            VERBATIM
            )

    add_custom_command(OUTPUT images
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_CURRENT_BINARY_DIR}/images
            DEPENDS ${SHOWCASE_SOURCES}
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Copying images to build directory"
            VERBATIM)

    add_custom_target(presentation ALL
            DEPENDS ${HTML_SHOWCASE} images
            VERBATIM
            )
else()
    message(CHECK_FAIL "not found. HTML presentation will not be built")
endif()