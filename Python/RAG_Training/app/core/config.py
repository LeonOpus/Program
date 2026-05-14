from dataclasses import dataclass
import os


def _to_bool(value: str | None, default: bool = False) -> bool:
    if value is None:
        return default
    return value.strip().lower() in {"1", "true", "yes", "on"}


@dataclass(frozen=True)
class Settings:
    app_name: str = "llm-engineering-30days"
    debug: bool = False


def get_settings() -> Settings:
    return Settings(
        app_name=os.getenv("APP_NAME", "llm-engineering-30days"),
        debug=_to_bool(os.getenv("DEBUG"), default=False),
    )


settings = get_settings()
