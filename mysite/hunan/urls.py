from django.urls import path

from . import views

app_name = 'hunan'

urlpatterns = [
    path('', views.index, name='index'),
    path('search/', views.search, name='search'),
    path('detail/<int:id>/', views.detail, name='detail'),
    path('type/<int:classify_id>/', views.data_list_with_type, name='type'),
    path('year/<int:year_id>/', views.data_list_with_year, name='year'),
]
