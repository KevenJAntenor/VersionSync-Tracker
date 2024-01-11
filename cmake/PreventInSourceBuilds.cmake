#
# This function will prevent in-source builds
function(AssureOutOfSourceBuilds)
  # make sure the user doesn't play dirty with symlinks
  get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
  get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

  # disallow in-source builds
  if("${srcdir}" STREQUAL "${bindir}")
    message("######################################################")
    message("# Ne pas compiler directement dans les sources.       ")
    message("# Créer un répertoire build spécifiquement pour cela. ")
    message("#                                                     ")
    message("# CMake a déjà créé plusieurs fichiers. Le mieux est  ")
    message("# de supprimer ce répertoire et de décompresser de    ")
    message("# nouveau.                                            ")
    message("#                                                     ")
    message("# Si vous utilisez git, faites ceci pour nettoyer:    ")
    message("#  git clean -fdx                                     ")
    message("######################################################")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

AssureOutOfSourceBuilds()
