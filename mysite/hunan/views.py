from django.shortcuts import render
from django.core.paginator import Paginator
from django.views.generic import View, ListView, FormView
from django.db.models import Q

from .models import City, Year, Category

import jieba


# Create your views here.
def index(request):
    return render(request, 'hunan/index.html')


def detail(request, id):
    data = City.objects.get(id=id)
    kws = data.keywords.split(' ')[:10]
    return render(request, 'hunan/detail.html', {'data': data, 'topKws': kws})


def data_list(request, datasets):
    type_list = Category.objects.all().distinct()
    year_list = Year.objects.all().distinct()

    page_num = request.GET.get('page', 1)
    p = Paginator(datasets, 6)
    page_list = p.get_page(page_num)

    return render(request, 'hunan/data_list.html', {
        'total_num': p.count,
        'page_obj': page_list,
        'typeList': type_list,
        'yearList': year_list,
    })


def data_list_with_type(request, classify_id):
    page_list = City.objects.filter(classify_id=classify_id)
    return data_list(request, page_list)


def data_list_with_year(request, year_id):
    page_list = City.objects.filter(year_id=year_id)
    return data_list(request, page_list)


def search(request):
    if request.method == "POST":
        search_text = request.POST.get('searchText')
        request.session['searchText'] = search_text
    else:
        search_text = request.session.get('searchText')

    print(search_text)
    keywords = set(jieba.cut_for_search(search_text))

    cities = {'长沙', '株洲', '湘潭', '衡阳', '邵阳', '岳阳', '常德', '张家界', '益阳', '郴州', '永州', '怀化', '娄底', '湘西'}
    category = {'体育', '财经', '房产', '家居', '教育', '科技', '时尚', '时政', '游戏', '娱乐'}
    years = {'2016', '2017', '2018', '2019'}

    valid_keywords = {
        'name': cities,
        'category__category': category,
        'year__year': years,
    }
    Q_all = Q()
    for k, v in valid_keywords.items():
        q = Q()
        q.connector = 'OR'
        for item in keywords & v:
            print(k, item)
            q.children.append((k, item))
        Q_all.add(q, 'AND')

    results = City.objects.filter(Q_all).only('id', 'keywords')
    return data_list(request, results)


class SearchListView(FormView):
    context_object_name = 'searchList'
    template_name = 'hunan/data_list.html'
    paginate_by = 6
    model = City
    http_method_names = [u'post', ]

    def get_context_data(self, *, object_list=None, **kwargs):
        context = super().get_context_data(**kwargs)
        context['typeList'] = Category.objects.all()
        context['yearList'] = Year.objects.all()
        return context
