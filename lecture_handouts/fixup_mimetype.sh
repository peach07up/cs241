#!/bin/bash
svn propset svn:mime-type 'binary' *.pdf
svn propset svn:mime-type 'application/vnd.openxmlformats-officedocument.wordprocessingml.document' C*docx
