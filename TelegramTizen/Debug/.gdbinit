python
import sys
sys.path.insert(0, "/home/sandeep/tizen-sdk-2.4/tools/python")
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
from osp.printers import register_osp_printers
register_osp_printers (None)
end
