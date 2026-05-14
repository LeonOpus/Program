from fastapi import FastAPI

from app.api import api_router
from app.core.config import settings
from app.core.logging import setup_logging

setup_logging(debug=settings.debug)

app = FastAPI(title=settings.app_name, debug=settings.debug)
app.include_router(api_router)
